// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"


void UInGameMenu::NativeConstruct()
{
    if(QuitButton == nullptr) return;
    QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitServer);

    if(CancelButton == nullptr) return;
    CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelMenu);

    SetIsFocusable(true);
}

void UInGameMenu::QuitServer()
{
    if(m_MenuInterface == nullptr) return;
    this->RemoveFromParent();
    m_MenuInterface->LoadMainMenu();
}

void UInGameMenu::CancelMenu()
{
    Teardown();
}
