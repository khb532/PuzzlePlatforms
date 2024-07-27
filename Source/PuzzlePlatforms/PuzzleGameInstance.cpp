// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"


UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("Constructor has called"));
}

void UPuzzleGameInstance::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("Init has called"));
}

void UPuzzleGameInstance::Host(void)
{
    UEngine* Engine = GetEngine();                                                      // GameInstance::GetEngine()
    if(Engine == nullptr)
        return;
    Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));              // #include Engine/Engine.h

    UWorld* World = GetWorld();
    if(World == nullptr)
        return;

    World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");                // UWorld::ServerTravel()
                                                                                        // ?listen 인자 없으면 서버로 작동하지않음
}

void UPuzzleGameInstance::Join(const FString& address)
{
    UEngine* Engine = GetEngine();
    if(Engine != nullptr)
    {
        Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *address));

        APlayerController* PlayerController = GetFirstLocalPlayerController();
        if(!ensure(PlayerController != nullptr)) return;

        PlayerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
    }
}
