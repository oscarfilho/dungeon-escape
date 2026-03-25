// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	UE_LOG(LogTemp, Display, TEXT("My Owner called name is: %s"), *MyOwner->GetActorNameOrLabel());
	StartLocation = MyOwner->GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("%s is located at: %s"), *MyOwner->GetActorNameOrLabel(), *StartLocation.ToCompactString());
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	CurrentLocation.Z = CurrentLocation.Z + 100.0f * DeltaTime;
	GetOwner()->SetActorLocation(CurrentLocation);
}

