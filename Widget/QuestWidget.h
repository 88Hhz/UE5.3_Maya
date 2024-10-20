// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class MAYA53_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void SetQuest(const FString& Content);

	void ClearQuest();

private:
	void PlayFadeInAnim();

	void PlayFadeOutAnim();

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestContent;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* QuestFadeIn;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* QuestFadeOut;


	UPROPERTY()
	bool bClear = false;
};
