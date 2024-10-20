// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestManager.generated.h"

class UQuestWidget;
/**
 * 
 */
UCLASS()
class MAYA53_API UQuestManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetQuest(const FString& Content);

	void SetQuestWidget(UQuestWidget* Widget);

	UFUNCTION(BlueprintCallable)
	void SetCurrentWidget(int32 QuestIndex);

	UFUNCTION(BlueprintCallable)
	void ClearCurrentQuest();

	UPROPERTY()
	UQuestWidget* QuestWidget;

	UPROPERTY()
	TArray<FString> QuestContents;

	UPROPERTY()
	int32 CurrentQuestIndex = 0;
};
