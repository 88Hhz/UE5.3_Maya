// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MAYA53_API AMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	AMenuGameModeBase();

protected:
	virtual void BeginPlay() override;
};
