// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "UE5T5BoxTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE5T5_API UUE5T5BoxTriggerComponent : public UBoxComponent
{
   GENERATED_BODY()
   UUE5T5BoxTriggerComponent();
   
protected:
   virtual void BeginPlay() override;

};
