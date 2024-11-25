// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE5T5GrabObj.h"
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
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
    TArray<TObjectPtr<AUE5T5GrabObj>> GrabbedObjects;
    TArray<TObjectPtr<AUE5T5GrabObj>> GrabbedReleaseObjects;
};
