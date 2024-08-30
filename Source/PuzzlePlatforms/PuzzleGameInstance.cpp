// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "TriggerPlatform.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
#include "Blueprint/UserWidget.h"


UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("Constructor has called"));

    // #include "UObject/ConstructorHelpers.h" : 생성자에서만 사용
    // #include "Blueprint/USerWidget.h" : build.cs  UMG 모듈 추가
    // FClassFinder<T> : 문자열 참조, 구조체 선언문, 생성자로 찾을 파일의 경로 전달
    ConstructorHelpers::FClassFinder<UUserWidget> MMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
    if(MMenuBPClass.Class != NULL)
    {
        MainMenuClass = MMenuBPClass.Class;
    }

    ConstructorHelpers::FClassFinder<UUserWidget> IMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
    if(IMenuBPClass.Class != NULL)
    {
        InGameMenuClass = IMenuBPClass.Class;
    }
}

void UPuzzleGameInstance::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("Init has called"));
    UE_LOG(LogTemp, Warning, TEXT("MainMenu Class : %s"), *MainMenuClass->GetName());
    UE_LOG(LogTemp, Warning, TEXT("InGameMenu Class : %s"), *InGameMenuClass->GetName());
}

void UPuzzleGameInstance::Host(void)
{
    if(MMenu == nullptr) return;
    MMenu->RemoveFromParent();                                                           // Menu 마우스 잠금 해제

    UEngine* Engine = GetEngine();                                                      // GameInstance::GetEngine()
    if(Engine == nullptr) return;
    Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));              // #include Engine/Engine.h

    UWorld* World = GetWorld();
    if(World == nullptr) return;
    World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");                // UWorld::ServerTravel()
                                                                                        // CMD로 실행할때 뒤에 명령어
                                                                                        // ?listen 인자 없으면 서버로 작동하지않음
}

void UPuzzleGameInstance::Join(const FString& address)
{
    if(MMenu == nullptr) return;
    MMenu->RemoveFromParent();

    UEngine* Engine = GetEngine();
    if(Engine != nullptr)
    {
        Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *address));

        APlayerController* PlayerController = GetFirstLocalPlayerController();
        if(!ensure(PlayerController != nullptr)) return;

        PlayerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
    }
}

void UPuzzleGameInstance::LoadMenu()
{
    // Menu 생성, 뷰포트에 연결
    if(MainMenuClass == NULL) return;
    // UUserWidget >>> UMainMenu
    MMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
    
    if(MMenu == nullptr) return;
    MMenu->Setup();
    MMenu->SetMenuInterface(this);                                                       // m_MenuInterface = PuzzleGameInstance;
}

void UPuzzleGameInstance::LoadInGameMenu()
{
    if(InGameMenuClass == NULL) return;
    UMenuWidget* IMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);

    if(IMenu == nullptr) return;
    IMenu->Setup();
    IMenu->SetMenuInterface(this);
}
