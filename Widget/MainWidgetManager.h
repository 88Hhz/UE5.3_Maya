// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MainWidgetManager.generated.h"


class UMayaMainWidget;
/**
 * 
 */
UCLASS()
class MAYA53_API UMainWidgetManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void SetMainWidget(UMayaMainWidget* Widget);

	FORCEINLINE UMayaMainWidget* GetMainWidget() const { return MayaMainWidget; }

	UFUNCTION(BlueprintCallable, Category = "Function")
	void SetHpPercent(float Inpercent);

	UFUNCTION(BlueprintCallable, Category = "Function")
	void SetStaminaPercent(float InPercent);

	UFUNCTION(BlueprintCallable, Category = "Function")
	void SetManaPercent(float InPercent);

private:
	UPROPERTY()
	UMayaMainWidget* MayaMainWidget;
};

