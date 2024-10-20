// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MayaGameInstance.generated.h"


class UQuestManager;
/**
 * 
 */
UCLASS()
class MAYA53_API UMayaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMayaGameInstance();

	void RstGameInstance();

	UFUNCTION(BlueprintCallable, Category = "CharacterFunction")
	void SaveCharacterStats(float Hp, float Mana, float Stamina);

	UFUNCTION(BlueprintCallable, Category = "CharacterFunction")
	void RstCharacterStats();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = LevelName)
	FString CurrentLevelName;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Level)
	bool bIsRetry;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = PlayerStats)
	float PlayerHp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = PlayerStats)
	float PlayerMana;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = PlayerStats)
	float PlayerStamina;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Interact)
	bool bInteractConversation;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Interact)
	bool bInteractLevel;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Quest)
	int32 QuestNum;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Quest)
	int32 MonsterNum;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Quest)
	bool bClearTroon;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Quest)
	bool bClearSuccubus;



protected:
	virtual void Init() override;
};
