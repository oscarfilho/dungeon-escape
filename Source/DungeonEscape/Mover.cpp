// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

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

	TargetLocation = StartLocation + MoveOffset;
	UE_LOG(LogTemp, Display, TEXT("%s is located at: %s"), *MyOwner->GetActorNameOrLabel(), *StartLocation.ToCompactString());
	UE_LOG(LogTemp, Display, TEXT("Start Location: %s, Target Location: %s"), *StartLocation.ToCompactString(), *TargetLocation.ToCompactString());
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	float Speed = MoveOffset.Length() / MoveTime;

	if (ShouldMove)
	{
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);
	}
	else {
		FVector InitialLocation = FMath::VInterpConstantTo(CurrentLocation, StartLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(InitialLocation);
	}
}

