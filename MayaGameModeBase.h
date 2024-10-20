// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MayaGameModeBase.generated.h"

class UMayaGameInstance;
class UQuestManager;
/**
 * 
 */
UCLASS()
class MAYA53_API AMayaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMayaGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "Function")
	void ChangeLevel(const FString& LevelName);

	UFUNCTION(BlueprintCallable, Category = "Function")
	void PauseGame(bool bPause);


protected:
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, Category = "LevelName")
	FString CurrentLevelName;


};
