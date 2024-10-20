// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/QuestManager.h"
#include "QuestWidget.h"

void UQuestManager::SetQuest(const FString& Content)
{
	if (QuestContents.Num() < 7)
	{
		QuestContents.Add(Content);
	}
}

void UQuestManager::SetQuestWidget(UQuestWidget* Widget)
{
	QuestWidget = Widget;
}

void UQuestManager::ClearCurrentQuest()
{
	if (CurrentQuestIndex < 7)
	{
		QuestWidget->ClearQuest();
		CurrentQuestIndex++;
	}
}

void UQuestManager::SetCurrentWidget(int32 QuestIndex)
{

	QuestWidget->SetQuest(QuestContents[QuestIndex]);
}
