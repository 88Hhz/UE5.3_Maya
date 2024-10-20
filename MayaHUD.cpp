// Fill out your copyright notice in the Description page of Project Settings.


#include "MayaHUD.h"
#include "MayaGameInstance.h"

#include "MainMenuWidget.h"
#include "MayaMainWidget.h"
#include "BossHpWidget.h" 

#include "MayaPlayerController.h"
#include "Kismet/GameplayStatics.h"




void AMayaHUD::BeginPlay()
{
	Super::BeginPlay();

	if (WBP_SettingWidget)
	{
		SettingWidget = CreateWidget(GetWorld(), WBP_SettingWidget);
		SettingWidget->AddToViewport();
	}

	bVisibleSetting = false;
	UMayaGameInstance* GI = Cast<UMayaGameInstance>(GetGameInstance());
	if (GI)
	{
		CurrentLevelName = GI->CurrentLevelName;
		SetWidgetWithLevel();
	}
}


void AMayaHUD::SetWidgetWithLevel()
{
	//메인 메뉴 레벨
	if (CurrentLevelName.Equals(TEXT("MainMenu"), ESearchCase::CaseSensitive))
	{
		if (MainWidget)
		{
			MainWidget->RemoveFromParent();
			MainWidget = nullptr;
		}
		if (QuestWidget)
		{
			QuestWidget->RemoveFromParent();
			QuestWidget = nullptr;
		}

		if (WBP_MainMenuWidget)
		{
			MenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), WBP_MainMenuWidget);
			MenuWidget->AddToViewport();
		}
		ChangeMenuWidget();
	}
	else
	{
		if (MenuWidget)
		{
			MenuWidget->RemoveFromParent();
			MenuWidget = nullptr;
		}

		if (WBP_MayaMainWidget)
		{
			MainWidget = CreateWidget<UMayaMainWidget>(GetWorld(), WBP_MayaMainWidget);
			MainWidget->AddToViewport();
		}
		if (WBP_QuestWidget)
		{
			QuestWidget = CreateWidget(GetWorld(), WBP_QuestWidget);
			QuestWidget->AddToViewport();
		}
		ChangeMainWidget();
	}
}


void AMayaHUD::ChangeMenuWidget()
{
	if (!bVisibleSetting)
	{
		MenuWidget->SetVisibility(ESlateVisibility::Visible);
		SettingWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		MenuWidget->SetVisibility(ESlateVisibility::Hidden);
		SettingWidget->SetVisibility(ESlateVisibility::Visible);
	}
	bVisibleSetting = !bVisibleSetting;
}

void AMayaHUD::ChangeMainWidget()
{
	if (!bVisibleSetting)
	{
		MainWidget->SetVisibility(ESlateVisibility::Visible);
		SettingWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		MainWidget->SetVisibility(ESlateVisibility::Hidden);
		SettingWidget->SetVisibility(ESlateVisibility::Visible);
	}
	bVisibleSetting = !bVisibleSetting;
}

void AMayaHUD::ChangeGameoverWidget()
{
	if (WBP_GameoverWidget)
	{
		GameoverWidget = CreateWidget(GetWorld(), WBP_GameoverWidget);
		GameoverWidget->AddToViewport(1);
	}
	if (MainWidget)
	{
		MainWidget->RemoveFromParent();
		MainWidget = nullptr;
	}
	if (QuestWidget)
	{
		QuestWidget->RemoveFromParent();
		QuestWidget = nullptr;
	}
}
