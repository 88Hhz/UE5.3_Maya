// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossHpWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class MAYA53_API UBossHpWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Function")
	void SetBossName(const FString& name);

	UFUNCTION(BlueprintCallable, Category = "Function")
	void SetHpPercent(float InPercent);
private:
	FTimerHandle FHpHandle;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Hp_Bar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Hp_BackBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BossName;

	float TargetHp;
	void Hp_Lerp();
};
