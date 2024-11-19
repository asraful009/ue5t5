// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UE5T5PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE5T5_API AUE5T5PlayerController : public APlayerController
{
	GENERATED_BODY()
	
	AUE5T5PlayerController();

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	// Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> GrabAction;
	
public:
	UFUNCTION(Category="Input")
	void OnMoveEvent(const FInputActionValue& Value);
	UFUNCTION(Category="Input")
	void OnLookEvent(const FInputActionValue& Value);
	UFUNCTION(Category="Input")
	void OnGrabEvent(const FInputActionValue& Value);

};
