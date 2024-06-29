// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float Speed = 20.f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	void AddActiveTrigger();	// ActiveTrigger +1 // TriggerPlatform에서 호출
	void RemoveActiveTrigger();	// ActiveTrigger -1 // TriggerPlatform에서 호출

private:
	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;
	
	void SwapLocation(FVector Loc1, FVector Loc2);

	UPROPERTY(EditAnywhere)		// >=1 : Activated / <1 : DeActivated
	int ActiveTriggers = 1;		// AddActiveTrigger, RemoveActiveTriger 에서 +-


	
};
