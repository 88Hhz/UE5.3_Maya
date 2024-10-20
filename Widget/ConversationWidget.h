// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConversationWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class MAYA53_API UConversationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void SetConversation(const FString& Speaker, const FString& content);

protected:
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeAnim;

private:
	void SetContentSubstring();
	void PlayFadeAnim();

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SpeakerText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ContentText;

	FString FullContent;
	FString CurrentContent;

	FTimerHandle TypeWriterTimerHandle;
	FTimerHandle ClearContentHandle;

};
