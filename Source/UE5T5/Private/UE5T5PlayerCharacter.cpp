// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5T5PlayerCharacter.h"

#include "UE5T5GrabObj.h"
#include "Components/CapsuleComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values
AUE5T5PlayerCharacter::AUE5T5PlayerCharacter()
{
     // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    GetCapsuleComponent()->InitCapsuleSize(40.0f, 90.0f);

    // Set movement properties
    BaseTurnRate = 45.0f;
    BaseLookUpRate = 45.0f;

    // Don't rotate when the controller rotates
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = false;

    // Create and setup the camera component
    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
    FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
    FirstPersonCamera->bUsePawnControlRotation = true;
    OwnedPhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

// Called when the game starts or when spawned
void AUE5T5PlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (!OwnedPhysicsHandle)
    {
        UE_LOG(LogTemp, Error, TEXT("Physics Handle Not Initialized!"));
        PrimaryActorTick.bCanEverTick = false;
    } else {
        // OwnedPhysicsHandle->InterpolationSpeed = 100.0f; // Adjust for your needs
        // OwnedPhysicsHandle->LinearStiffness = 1000.0f;
        // OwnedPhysicsHandle->LinearDamping = 200.0f;
        // OwnedPhysicsHandle->AngularStiffness = 1000.0f;
        // OwnedPhysicsHandle->AngularDamping = 200.0f;
    }
}

// Called every frame
void AUE5T5PlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bIsGrabbable)
    {
        if (!bIsGrabbedSomeThing) {
            if (const FHitResult HitResult = PerformHit(); IsHitResultValid(HitResult))
            {
                ObjectToGrab = Cast<UPrimitiveComponent>(HitResult.GetActor()->GetRootComponent());
                if (ObjectToGrab != nullptr)
                {
                    ObjectToGrab->WakeAllRigidBodies();
                    bIsGrabbedSomeThing = true;
                    const FVector TargetLocation = HitResult.ImpactPoint;
                    // OwnedPhysicsHandle->GrabComponentAtLocationWithRotation(ObjectToGrab, NAME_None,
                    //     ObjectToGrab->GetComponentLocation(), ObjectToGrab->GetComponentRotation());
                    OwnedPhysicsHandle->GrabComponentAtLocationWithRotation(ObjectToGrab, NAME_None,
                        TargetLocation, ObjectToGrab->GetComponentRotation());
                }
            }
        }
        else if (bIsGrabbedSomeThing)
        {
            const FVector Location = FirstPersonCamera->GetComponentLocation() + FirstPersonCamera->GetForwardVector() * HoldDistance;
            const FRotator Rotation = GetActorRotation();
            OwnedPhysicsHandle->SetTargetLocationAndRotation(Location, Rotation);
            DrawDebugSphere(GetWorld(), Location, SweepRadius, 6, SweepHitColor, false, -1.0f, 0, 1.0f);

        }
    }
}

// Called to bind functionality to input
void AUE5T5PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUE5T5PlayerCharacter::OnMoveEventHandler(const FInputActionValue& Value)
{    
    const FVector2D MovementVector = Value.Get<FVector2D>();
    FVector2D FilteredMovementVector = FVector2D::ZeroVector;

    if (FMath::Abs(MovementVector.X) > DeadZone)
    {
        FilteredMovementVector.X = MovementVector.X;
    }
    if (FMath::Abs(MovementVector.Y) > DeadZone)
    {
        FilteredMovementVector.Y = MovementVector.Y;
    }
    
    const FVector2D NormalizationMovementVector = FilteredMovementVector.GetSafeNormal();
    SmoothedMovementVector = FMath::Lerp(SmoothedMovementVector, NormalizationMovementVector, 0.1f);

    // Find out which way is forward
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    
    AddMovementInput(ForwardDirection, SmoothedMovementVector.Y);
    AddMovementInput(RightDirection, SmoothedMovementVector.X);    
}

void AUE5T5PlayerCharacter::OnLookEventHandler(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();
    FVector2D FilteredLookAxisVector = FVector2D::ZeroVector;
    // Apply dead zone filtering
    if (FMath::Abs(LookAxisVector.X) > DeadZone)
    {
        FilteredLookAxisVector.X = LookAxisVector.X;
    }
    if (FMath::Abs(LookAxisVector.Y) > DeadZone)
    {
        FilteredLookAxisVector.Y = LookAxisVector.Y;
    }
    const float SmoothingFactor = (LookAxisVector.Size() > 1.0f) ? 0.97f : 0.5f;

    SmoothedLookVector =
        FMath::Lerp(SmoothedLookVector, FilteredLookAxisVector.GetSafeNormal(), SmoothingFactor); // Adjust alpha for smoothness

    AddControllerYawInput(SmoothedLookVector.X * BaseTurnRate * GetWorld()->GetDeltaSeconds());
    AddControllerPitchInput(FMath::Clamp(SmoothedLookVector.Y * BaseLookUpRate * GetWorld()->GetDeltaSeconds(), -MaxPitchAngle, MaxPitchAngle));
}

void AUE5T5PlayerCharacter::OnGrabEventHandler(const bool bIsGrabbed)
{
    UE_LOG(LogTemp, Warning, TEXT("Grab Event"));
    bIsGrabbable = bIsGrabbed;
    if (bIsGrabbed == false && bIsGrabbedSomeThing)
    {
        if (OwnedPhysicsHandle && OwnedPhysicsHandle->GrabbedComponent)
        {
            OwnedPhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
            OwnedPhysicsHandle->ReleaseComponent();
            bIsGrabbedSomeThing = false;
            ObjectToGrab = nullptr;
        }
    }
}

FHitResult AUE5T5PlayerCharacter::PerformHit()
{
    if (GetWorld() == nullptr) return FHitResult();
    if (OwnedPhysicsHandle == nullptr) return FHitResult();
    
    // Get start location (camera location)
    const FVector StartLocation = FirstPersonCamera->GetComponentLocation();
    // Get forward vector from camera rotation
    const FVector ForwardVector = FirstPersonCamera->GetForwardVector();
    // Calculate end location
    const FVector EndLocation = StartLocation + (ForwardVector * SweepDistance);

    // Setup collision params
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this); // Ignore self
    QueryParams.bTraceComplex = true;  // Use complex collision

    // Setup shape of sweep (sphere in this case)
    const FCollisionShape SweepShape = FCollisionShape::MakeSphere(SweepRadius);

    // Hit result
    FHitResult HitResult;
    
    const bool bHit = GetWorld()->SweepSingleByChannel(
       HitResult,
       StartLocation,
       EndLocation,
       FQuat::Identity,
       SweepTraceChannel,
       SweepShape,
       QueryParams
   );
    if (bShowSweepDebug)
    {
        // Draw debug sphere at start [ Head ]
        DrawDebugSphere(
            GetWorld(),
            StartLocation,
            SweepRadius,
            8, // Segments
            FColor::Blue,
            false,
            -1.0f,
            0,
            0.4f
        );
    }
    if (bHit)
    {
        if (bShowSweepDebug)
        {
            // Draw debug sphere at hit location
            DrawDebugSphere(
                GetWorld(),
                HitResult.Location,
                SweepRadius,
                16,
                SweepHitColor,
                false,
                -1.0f,
                0,
                1.0f
            );

            // Draw line from start to hit location
            DrawDebugLine(
                GetWorld(),
                StartLocation,
                HitResult.Location,
                SweepHitColor,
                false,
                -1.0f,
                0,
                2.0f
            );

            // Draw normal at hit location
            DrawDebugLine(
                GetWorld(),
                HitResult.Location,
                HitResult.Location + (HitResult.Normal * 50.0f),
                FColor::Yellow,
                false,
                -1.0f,
                0,
                2.0f
            );
        }
        
        if (HitResult.GetActor())
        {
            DrawDebugString(
                GetWorld(),
                HitResult.Location,
                HitResult.GetActor()->GetName(),
                nullptr,
                FColor::White,
                0.0f
            );
            if (Cast<AUE5T5GrabObj>(HitResult.GetActor()))
            {
                return HitResult;
            } 
            return FHitResult();
        }
    }
    else
    {
        if (bShowSweepDebug)
        {
            // If no hit, draw sphere at end location
            DrawDebugSphere(
                GetWorld(),
                EndLocation,
                SweepRadius,
                16,
                SweepNoHitColor,
                false,
                -1.0f,
                0,
                1.0f
            );

            // Draw line for full trace
            DrawDebugLine(
                GetWorld(),
                StartLocation,
                EndLocation,
                SweepNoHitColor,
                false,
                -1.0f,
                0,
                2.0f
            );
        }
    }
    return FHitResult();
}

bool AUE5T5PlayerCharacter::IsHitResultValid(const FHitResult& HitResult)
{
    return HitResult.bBlockingHit ||
    (
        (HitResult.GetActor() != nullptr || HitResult.GetComponent() != nullptr)
        && HitResult.GetComponent()->IsSimulatingPhysics()
    );
}