// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5T5PlayerController.h"

#include "UE5T5PlayerCharacter.h"

AUE5T5PlayerController::AUE5T5PlayerController()
{
    
}

void AUE5T5PlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        if (DefaultMappingContext)
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void AUE5T5PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {        
        if (MoveAction)
        {
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUE5T5PlayerController::OnMoveEvent);
        }

        if (LookAction)
        {
            EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUE5T5PlayerController::OnLookEvent);
        }

        if (GrabAction)
        {
            EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, this, &AUE5T5PlayerController::OnGrabEvent);
            EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Completed, this, &AUE5T5PlayerController::OnGrabEvent);
        }
    }
}

void AUE5T5PlayerController::OnMoveEvent(const FInputActionValue& Value)
{
    if (const TObjectPtr<AUE5T5PlayerCharacter> PlayerCharacter = Cast<AUE5T5PlayerCharacter>(GetCharacter()))
    {
        PlayerCharacter->OnMoveEventHandler(Value);
    }
}

void AUE5T5PlayerController::OnLookEvent(const FInputActionValue& Value)
{
    if (const TObjectPtr<AUE5T5PlayerCharacter> PlayerCharacter = Cast<AUE5T5PlayerCharacter>(GetCharacter()))
    {
        PlayerCharacter->OnLookEventHandler(Value);
    }
}

void AUE5T5PlayerController::OnGrabEvent(const FInputActionValue& Value)
{
    if (const TObjectPtr<AUE5T5PlayerCharacter> PlayerCharacter = Cast<AUE5T5PlayerCharacter>(GetCharacter()))
    {
        const bool bIsGrabbed = Value.Get<bool>();
        PlayerCharacter->OnGrabEventHandler(bIsGrabbed);
    }
}
