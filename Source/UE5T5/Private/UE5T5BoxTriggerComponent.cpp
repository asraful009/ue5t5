// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5T5BoxTriggerComponent.h"

UUE5T5BoxTriggerComponent::UUE5T5BoxTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true; // Enable ticking for this component

    SetGenerateOverlapEvents(true); // Enable overlap events
}

void UUE5T5BoxTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
    OnComponentBeginOverlap.AddDynamic(this, &UUE5T5BoxTriggerComponent::OnOverlapBegin);
    OnComponentEndOverlap.AddDynamic(this, &UUE5T5BoxTriggerComponent::OnOverlapEnd);

}

void UUE5T5BoxTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (GrabbedObjects.Num() > 0)
    {
        FString Names = "";
        for (const TObjectPtr<AUE5T5GrabObj>& GrabObj : GrabbedObjects)
        {
            if (GrabObj)
            {
                Names += "" + GrabObj->GetName() + "\n";
            }
        }
        // Draw the debug text
        DrawDebugString(
            GetWorld(),
            GetOwner()->GetActorLocation() + FVector(0, 0, 50),
            Names,
            nullptr,
            FColor::Green,
            0.0f, // Duration: 0 means it will stay until next Tick
            true  // Draw shadow for better visibility
        );
    }
}

void UUE5T5BoxTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    

    if (OtherActor != nullptr && OtherActor->ActorHasTag("UE5T5_BOX_PICKUP"))
    {
        UE_LOG(LogTemp, Warning, TEXT("Overlap Begin: %s"), *OtherActor->GetName());
        const TObjectPtr<AUE5T5GrabObj> GrabObj = Cast<AUE5T5GrabObj>(OtherActor);
        if (GrabObj)
        {
            GrabbedObjects.Add(GrabObj);
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("GrabbedObjects: %d"), GrabbedObjects.Num());
}

void UUE5T5BoxTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    

    if (OtherActor != nullptr && OtherActor->ActorHasTag("UE5T5_BOX_PICKUP"))
    {
        const TObjectPtr<AUE5T5GrabObj> GrabObj = Cast<AUE5T5GrabObj>(OtherActor);
        if (GrabObj && GrabbedObjects.Contains(GrabObj))
        {
            GrabbedObjects.Remove(GrabObj);
            UE_LOG(LogTemp, Warning, TEXT("Removed from GrabbedObjects: %s"), *OtherActor->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Actor not found in GrabbedObjects: %s"), *OtherActor->GetName());
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("GrabbedObjects: %d"), GrabbedObjects.Num());
}
