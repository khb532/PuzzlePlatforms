// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlatform.h"
#include "Components/BoxComponent.h"

#include "MovingPlatform.h"

// Sets default values
ATriggerPlatform::ATriggerPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Volume"));
	if(TriggerVolume == nullptr)
		return;

	RootComponent = TriggerVolume;

}

// Called when the game starts or when spawned
void ATriggerPlatform::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this,&ATriggerPlatform::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ATriggerPlatform::OnOverlapEnd);
	
}

// Called every frame 
void ATriggerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerPlatform::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for(AMovingPlatform* Platform : PlatformToTrigger)
	{
		// Tarray<MovingPlatform*> PlatformToTrigger 순회
		// 지정된 MovingPlatform의 ActiveTrigger +1
		Platform->AddActiveTrigger();
	}
}

void ATriggerPlatform::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for(AMovingPlatform* Platform : PlatformToTrigger)
	{
		Platform->RemoveActiveTrigger();
	}
}

