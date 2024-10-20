// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MayaHUD.generated.h"

class UMainMenuWidget;
class UMayaMainWidget;

class UBossHpWidget;

/**
 * 
 */
UCLASS()
class MAYA53_API AMayaHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Function)
	void ChangeMenuWidget();

	UFUNCTION(BlueprintCallable, Category = Function)
	void ChangeMainWidget();

	UFUNCTION(BlueprintCallable, Category = Function)
	void ChangeGameoverWidget();

	UFUNCTION(BlueprintCallable, Category = Function)
	FORCEINLINE UMainMenuWidget* GetMenuWidget() const { return MenuWidget; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "MapName")
	FString CurrentLevelName;

	UFUNCTION(BlueprintCallable, Category = Function)
	void SetWidgetWithLevel();

private:
	UPROPERTY(EditDefaultsOnly, Category = "WidgetBP")
	TSubclassOf<UMainMenuWidget> WBP_MainMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetBP")
	TSubclassOf<UMayaMainWidget> WBP_MayaMainWidget;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetBP")
	TSubclassOf<UUserWidget> WBP_SettingWidget;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetBP")
	TSubclassOf<UUserWidget> WBP_QuestWidget;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetBP")
	TSubclassOf<UUserWidget> WBP_GameoverWidget;

	UPROPERTY()
	UMainMenuWidget* MenuWidget;

	UPROPERTY()
	UMayaMainWidget* MainWidget;

	UPROPERTY()
	UUserWidget* SettingWidget;

	UPROPERTY()
	UUserWidget* QuestWidget;

	UPROPERTY()
	UUserWidget* GameoverWidget;

	bool bVisibleSetting;
};
