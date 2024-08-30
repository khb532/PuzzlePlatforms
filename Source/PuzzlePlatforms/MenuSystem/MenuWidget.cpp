// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"


void UMenuWidget::Setup()
{
    this->AddToViewport();
    /*
    게임실행시 마우스 커서가 보이지않음,  마우스가 인게임을 돌아다녀서 UI를 조작하지않음

    PlayerController -> SetInputMode ( FInputModeDataBase &Data ) 사용
    FInputModeData형 매개변수 요구, 구조체중 UIOnly 선택

    FInputModeUIOnly 멤버 두개 : MouseLockMode, WidgetToFocus 를 채워야함
        SetLockMouseToViewportBehavior ( EMouseLockMode InMouseLockMode ) 
        >> MouseLockMode setting function
        >>> EMouseLockMode::NotLock(창밖을 나갈수있음)

        ===================================================================

        SetWidgetToFocus ( TSharedPtr<SWidget> InWidgetToFocus ) 
        >> WidgetToFocus
        >>> Menu->TakeWidget()
            >> TSharedRef< SWidget > TakeWidget()
    */
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if(!ensure(PlayerController != nullptr)) return;

    PlayerController->bShowMouseCursor = true;

    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    PlayerController->SetInputMode(InputModeData);
}

void UMenuWidget::SetMenuInterface(IMainMenuInterface* MenuInterface)
{
    this->m_MenuInterface = MenuInterface; 
}

void UMenuWidget::NativeDestruct()
{
    Super::NativeDestruct();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if(!ensure(PlayerController != nullptr)) return;
    PlayerController->bShowMouseCursor = false;
    FInputModeGameOnly InputModeData;
    PlayerController->SetInputMode(InputModeData);
}
