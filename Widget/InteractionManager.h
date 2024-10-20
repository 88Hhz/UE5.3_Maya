// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InteractionManager.generated.h"

class UInteractionWidget;
class UMapInteraction;
/**
 * 
 */
UCLASS()
class MAYA53_API UInteractionManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
	void SetInteraction(bool bVisible);

	UFUNCTION(BlueprintCallable)
	void SetMapInteraction(int32 cnt);

	void SetInteractionWidget(UInteractionWidget* Widget);

	void SetMapInteractionWidget(UMapInteraction* Widget);

private:
	UPROPERTY()
	class UInteractionWidget* InteractionWidget;

	UPROPERTY()
	class UMapInteraction* MapInteraction;
};
