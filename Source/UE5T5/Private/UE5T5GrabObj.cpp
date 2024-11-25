// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5T5GrabObj.h"

// Sets default values
AUE5T5GrabObj::AUE5T5GrabObj()
{
     // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    SetRootComponent(StaticMesh);

    // Optionally configure additional properties
    StaticMesh->SetSimulatePhysics(true); // Enable physics simulation
    StaticMesh->SetCollisionProfileName(TEXT("PhysicsActor")); // Use a physics collision profile
}

// Called when the game starts or when spawned
void AUE5T5GrabObj::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AUE5T5GrabObj::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (Tags.Num() > 0)
    {
        FString Names = "";
        for (FName Tag :  Tags)
        {
            Names += "" + Tag.ToString() + "\n";
        }
        // Draw the debug text
        DrawDebugString(
            GetWorld(),
            GetActorLocation() + FVector(0, 0, 120),
            Names,
            nullptr,
            FColor::Green,
            0.0f, // Duration: 0 means it will stay until next Tick
            true  // Draw shadow for better visibility
        );
    }
}

