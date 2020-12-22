// Copyright Aghil Jose 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

	public:
	UOpenDoor();

	protected:
	virtual void BeginPlay() override;

	public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;


	private:
	float InitialYaw, CurrentYaw;
	AActor* ActorThatOpens;
	float DoorLastOpened = 0.0f;

	UPROPERTY(EditAnywhere)
		float MassToOpenDoors = 50.0f;
	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.5f;
	UPROPERTY(EditAnywhere)
		float TargetYaw;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

};
