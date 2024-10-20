// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class MAYA53_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void SetInteraction(bool bVisible);

protected:
	UPROPERTY(BlueprintReadOnly, transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeAnim;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_G;

private:
	void PlayAnim(bool bAnim);

};
