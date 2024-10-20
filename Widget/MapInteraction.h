// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapInteraction.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class MAYA53_API UMapInteraction : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void SetMapInteraction(int32 cnt);

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* MapNameImage;

	UPROPERTY(meta = (BindWidget))
	UImage* MapNameImage2;

	UPROPERTY(meta = (BindWidget))
	UImage* MapNameImage3;

	UPROPERTY(BlueprintReadOnly, transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* MapFadeIn;

	UPROPERTY(BlueprintReadOnly, transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* MapFadeOut;

private:
	void PlayFadeIn();
	void PlayFadeOut();

	FTimerHandle TimerHandle;

};
