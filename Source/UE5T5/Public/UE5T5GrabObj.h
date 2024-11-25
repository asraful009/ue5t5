// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE5T5GrabObj.generated.h"

UCLASS()
class UE5T5_API AUE5T5GrabObj : public AActor
{
    GENERATED_BODY()
    
public:    
    // Sets default values for this actor's properties
    AUE5T5GrabObj();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> StaticMesh;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

};
