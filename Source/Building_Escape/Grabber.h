// Copyright Aghil Jose 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

	public:
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();

	protected:
	virtual void BeginPlay() override;

	private:
	float Reach = 100.0f;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;

	FHitResult GetFirstPhysicsBodyInReach() const;
	FVector GetPlayersReach() const;
	FVector GetPlayersWorldPos() const;
};
