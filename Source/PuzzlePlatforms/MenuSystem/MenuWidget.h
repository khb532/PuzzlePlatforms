// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuInterface.h"
#include "MenuWidget.generated.h"

/**
MainMenu, InGameMenu 모두 Setup, SetMenuInterface, NativeDestruct 이용
MenuWidget.h 리팩토링
 */
UCLASS()
class PUZZLEPLATFORMS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup();
	void SetMenuInterface(IMainMenuInterface* MenuInterface);
	void Teardown();

protected:
	IMainMenuInterface* m_MenuInterface;	// MenuWidget상속받는 Main, Ingame에서 사용->protected
	
};
