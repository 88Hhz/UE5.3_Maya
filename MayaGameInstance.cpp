// Fill out your copyright notice in the Description page of Project Settings.


#include "MayaGameInstance.h"
#include "QuestManager.h"
#include "Kismet/GameplayStatics.h"

UMayaGameInstance::UMayaGameInstance()
{
	QuestNum = 0;
	MonsterNum = 0;
}


void UMayaGameInstance::Init()
{
	Super::Init();
	CurrentLevelName = TEXT("");

	QuestNum = 0;
	MonsterNum = 0;
	bIsRetry = false;

	PlayerHp = 200.f;
	PlayerMana = 200.f;
	PlayerStamina = 200.f;

	bInteractConversation = false;
	bInteractLevel = false;

	bClearTroon = false;
	bClearSuccubus = false;
}

void UMayaGameInstance::SaveCharacterStats(float Hp, float Mana, float Stamina)
{
	PlayerHp = Hp;
	PlayerMana = Mana;
	PlayerStamina = Stamina;
}

void UMayaGameInstance::RstCharacterStats()
{
	PlayerHp = 200.f;
	PlayerMana = 200.f;
	PlayerStamina = 200.f;
}

void UMayaGameInstance::RstGameInstance()
{
	this->Init();
}



