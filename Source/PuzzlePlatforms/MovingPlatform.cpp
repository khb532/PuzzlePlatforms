// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if(HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }

    GlobalStartLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(ActiveTriggers>0)    // Trigger ON 에서만 이동
    {
        if(HasAuthority())
        {
            FVector Location = GetActorLocation();  // Current Location
            FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
            Location += Speed * DeltaTime * Direction;
            SetActorLocation(Location);
            
            /*
            GStart로부터 현재의 거리가 FullDistance보다 크다면 Target을 지나친것
            -> Swap 조건
            */
            float FromStartDistance = (Location - GlobalStartLocation).Size();
            float FullDistance = (GlobalTargetLocation - GlobalStartLocation).Size();
            if(FullDistance <= FromStartDistance)
                SwapLocation(GlobalStartLocation, GlobalTargetLocation);
        }
    }

    
}

void AMovingPlatform::AddActiveTrigger()
{
    ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
    if(ActiveTriggers>0)
        ActiveTriggers--;
    else                        // 이미 0일경우 무시
        return;
}

void AMovingPlatform::SwapLocation(FVector Loc1, FVector Loc2)
{
    FVector Temp = Loc1;
    Loc1 = Loc2;
    Loc2 = Temp;
}

