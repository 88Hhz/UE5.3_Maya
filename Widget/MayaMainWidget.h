// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MayaMainWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class MAYA53_API UMayaMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void SetHpPercent(float InPercent);
	void SetStaminaPercent(float InPercent);
	void SetManaPercent(float InPercent);

private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Hp_Bar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Hp_BackBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Stamina_Bar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Stamina_BackBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Mana_Bar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Mana_BackBar;

	FTimerHandle FHpHandle;
	FTimerHandle FManaHandle;
	FTimerHandle FStaminaHandle;

	float TargetHp;
	float TargetStamina;
	float TargetMana;

	void Hp_Lerp();
	void Stamina_Lerp();
	void Mana_Lerp();
};
