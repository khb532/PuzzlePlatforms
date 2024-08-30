// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuInterface.h"

// Add default functionality here for any IMainMenuInterface functions that are not pure virtual.

/*
MenuInterface : Host()를 순수가상으로 선언

GameInstance.h : IMenuInterface를 상속
    MainMenu.h, m_Interface에 IMenuInterface를 상속하는 GameInstance의 포인터형 저장가능

MainMenu.h : 
    #include "Interface.h"
    IMenuInterface형 포인터 선언가능
        

MainMenu.cpp : 
    Setter 함수 선언
        m_Interface 멤버에 전달값 저장
    HostServer(),
        m_Interface -> Host()호출 : GameInstance->Host()        

GameInstance.cpp : 
    #include "MenuSystem/MainMenu.h"
    LoadMenu(),
        UUserWidget >>> UMainMenu 변경
        UMainMenu* Menu -> SetInterface(this) : Setter 함수로 this 전달하면서 호출
            MainMenu의 m_Interface는 GameInstance형 포인터 저장
*/