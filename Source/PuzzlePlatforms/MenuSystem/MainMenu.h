// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:	
	// meta = (BindWidget) : WBP_MainMenu, 위젯요소의 이름과 포인터이름이 일치해야함
	UPROPERTY(meta = (BindWidget))	
	class UButton* HostButton;	// Host Button Name
								// #include "Components/Button.h"
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinCancelButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;	// #include "Components/WidgetSwitcher.h"

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAdressField;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinSubButton;

	
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void CancelJoinMenu();
	
	UFUNCTION()
	void JoinServer();

};
