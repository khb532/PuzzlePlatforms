// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleGameInstance.generated.h"

/*

Terminal Order :: (PowerShell >> &command)
"UnrealEditor.exe path" "uproject path"
 /Game/Maps/--, ipadress
 -game, -server, -log

 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzleGameInstance : public UGameInstance
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
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& address);

	
};
