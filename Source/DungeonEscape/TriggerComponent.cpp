// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	UE_LOG(LogTemp, Display, TEXT("Trigger Component has been created!"));
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MoverActor) {
		Mover = MoverActor->FindComponentByClass<UMover>();
		if (Mover) {
			UE_LOG(LogTemp, Display, TEXT("Successfully found Mover Component"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Failed to find Mover Component"));
		}
	}else
		UE_LOG(LogTemp, Warning, TEXT("Move Actor is a null pointer!"));

	if (IsPressurePlate)
	{
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
		OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
	}
}


void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Display, TEXT("Seconds since begin play: %.3f"), GetWorld()->TimeSeconds);
}

void UTriggerComponent::Trigger(bool NewTriggerValue)
{
	IsTriggered = NewTriggerValue;
	if (Mover) {
		Mover->SetShouldMove(IsTriggered);
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("%s doesn't have a Mover to trigger!"), *GetOwner()->GetActorNameOrLabel());
	}
}


void UTriggerComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Overlap Begin!"));

	if (OtherActor && OtherActor->Tags.Contains("PressurePlateActivator") && Mover) {
		ActivatorCount++;

		if (!IsTriggered) {
			Trigger(true);
		}
	}
}

void UTriggerComponent::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Display, TEXT("Overlap End!"));

	if (OtherActor && OtherActor->Tags.Contains("PressurePlateActivator") && Mover) {
		ActivatorCount--;

		if (IsTriggered && !ActivatorCount) {
			Trigger(false);
		}
	}
}