// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Internationalization/Text.h"


bool UMainMenu::Initialize()
{
    bool SuperResult = Super::Initialize();
    if(SuperResult == false) return SuperResult;                        // if(!SuperResult) return false;

    if(HostButton == nullptr) return false;
    HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);     // Host 버튼에 HostServer() 다이내믹 연결

    if(JoinButton == nullptr) return false;
    JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

    if(JoinCancelButton == nullptr) return false;
    JoinCancelButton->OnClicked.AddDynamic(this, &UMainMenu::CancelJoinMenu);   

    if(JoinSubButton == nullptr) return false;
    JoinSubButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

    return true;
}

void UMainMenu::HostServer()
{
    if(m_MenuInterface != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hosting Server"));
        m_MenuInterface->Host();                                        // PuzzleGameInstance->Host();
    }
}

void UMainMenu::OpenJoinMenu()
{
    if(MenuSwitcher == nullptr) return;
    if(JoinMenu == nullptr) return;
    MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::CancelJoinMenu()
{
    if(MenuSwitcher == nullptr) return;
    if(MainMenu == nullptr)  return;
    MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
    if(IPAdressField == nullptr) return;
    const FString adress = IPAdressField->GetText().ToString();         // #include "Internationalization/Text.h"
    if(m_MenuInterface == nullptr) return;
    m_MenuInterface->Join(adress);
}



