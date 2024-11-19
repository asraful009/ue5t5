// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "UE5T5PlayerCharacter.generated.h"

UCLASS()
class UE5T5_API AUE5T5PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUE5T5PlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DeadZone = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	float SweepRadius = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	float SweepDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	float HoldDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	float InterpSpeed = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	TEnumAsByte<ECollisionChannel> SweepTraceChannel = ECC_GameTraceChannel1;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug|Sweep")
	bool bShowSweepDebug;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug|Sweep")
	TEnumAsByte<ECollisionChannel> SecondaryTraceChannel = ECC_Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug|Sweep")
	FColor SweepHitColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug|Sweep")
	FColor SecondaryHitColor = FColor::Yellow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug|Sweep")
	FColor SweepNoHitColor = FColor::Green;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug|Sweep")
	TEnumAsByte<ECollisionChannel> InteractableTraceChannel = ECC_GameTraceChannel1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Category="Input")
	void OnMoveEventHandler(const FInputActionValue& Value);
	
	UFUNCTION(Category="Input")
	void OnLookEventHandler(const FInputActionValue& Value);

	UFUNCTION(Category="Input")
	void OnGrabEventHandler(const bool bIsGrabbed);


private:
	FVector2D SmoothedMovementVector = FVector2D::ZeroVector;
	FVector2D SmoothedLookVector = FVector2D::ZeroVector;
	float MaxPitchAngle = 30.0f;
	bool bIsGrabbable = false;
	bool bIsGrabbedSomeThing = false;
	TObjectPtr<UPhysicsHandleComponent> OwnedPhysicsHandle;
	TObjectPtr<UPrimitiveComponent> ObjectToGrab;
	
	FHitResult PerformHit();
	bool IsHitResultValid(const FHitResult& HitResult);
};
