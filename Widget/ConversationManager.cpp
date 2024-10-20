// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationManager.h"
#include "ConversationWidget.h"


void UConversationManager::SetConversation(const FString& Speaker, const FString& Content)
{
	ConversationWidget->SetConversation(Speaker, Content);
}

void UConversationManager::SetConversationWidget(UConversationWidget* Widget)
{
	ConversationWidget = Widget;
}