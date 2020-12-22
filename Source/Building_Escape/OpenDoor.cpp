// Copyright Aghil Jose 2020


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += InitialYaw;

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has the open door on it. But no PressurePlate set."), *GetOwner()->GetName());
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (TotalMassOfActors() > MassToOpenDoors) {
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else {
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay) {
			CloseDoor(DeltaTime);
		}
	}

}

void UOpenDoor::OpenDoor(float DeltaTime) {
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator CurrentRotation(0.f, CurrentYaw, 0.f);
	CurrentRotation.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2.5f);
	GetOwner()->SetActorRotation(CurrentRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime) {
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator CurrentRotation(0.f, CurrentYaw, 0.f);
	CurrentRotation.Yaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, 2.5f);
	GetOwner()->SetActorRotation(CurrentRotation);
}

float UOpenDoor::TotalMassOfActors() const {
	float TotalMass = 0.0f;

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (AActor* OverlapActor : OverlappingActors) {
		TotalMass += OverlapActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}