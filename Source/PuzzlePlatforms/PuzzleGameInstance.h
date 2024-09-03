// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MainMenuInterface.h"
#include "PuzzleGameInstance.generated.h"

/*

Terminal Order :: (PowerShell >> &command)
"UnrealEditor.exe path" "uproject path"
 /Game/Maps/--, ipadress
 -game, -server, -log

 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzleGameInstance : public UGameInstance, public IMainMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init();

	/*
	UFUNCTION에 인자로 Exec가 가능한 클래스들
	@ PlayerControllers
		- Possessed Pawns
	@ HUD
	@ Cheat Manager
	@ GameMode
	@ GameInstance
	*/
	UFUNCTION(Exec)		// Exec : 콘솔명령어, 플레이중 콘솔에서 사용할 명령어 생성
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& address) override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION(BlueprintCallable)
	void LoadMainMenu() override;

private:
	/*
	WBP, widget c++ 생성 -> GameInstance c++
	생성자에서 WBP를 확보 : TSubClassOf<UUserWidget> Widget Class = FClassFinder<UUserWidget> Name.Class
	BlueprintCallable Function, LoadMenu() 구현
		menu(Widget.cpp) = CreateWidget<UUserWidget>(this, Widget Class)
		menu->Setup(),SetInterface(this)
	Level Blueprint -> GameInstance -> LoadMenu
	*/
	TSubclassOf<class UUserWidget> MainMenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* MMenu;
	class UMenuWidget* IMenu;
	
};
