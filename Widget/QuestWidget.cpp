// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuestWidget.h"
#include "QuestManager.h"
#include "Components/TextBlock.h"


void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!QuestContent)
	{
		UE_LOG(LogTemp, Error, TEXT("Quest Contents are not valid"));
		return;
	}
	if (!GetGameInstance() || !GetGameInstance()->GetSubsystem<UQuestManager>())
	{
		UE_LOG(LogTemp, Error, TEXT("QuestManager subsystem is not valid"));
		return;
	}
	GetGameInstance()->GetSubsystem<UQuestManager>()->SetQuestWidget(this);
	SetRenderOpacity(0.f);
}

void UQuestWidget::SetQuest(const FString& Content)
{
	QuestContent->SetText(FText::FromString(Content));
	SetRenderOpacity(1.f);
	PlayFadeInAnim();
}

void UQuestWidget::ClearQuest()
{
	PlayFadeOutAnim();
	//SetRenderOpacity(0.f);
}

void UQuestWidget::PlayFadeInAnim()
{
	if (!QuestFadeIn)
	{
		UE_LOG(LogTemp, Error, TEXT("FadeAnim is not set"));
		return;
	}
	PlayAnimation(QuestFadeIn);
}

void UQuestWidget::PlayFadeOutAnim()
{
	if (!QuestFadeOut)
	{
		UE_LOG(LogTemp, Error, TEXT("FadeAnim is not set"));
		return;
	}
	PlayAnimation(QuestFadeOut);
}
