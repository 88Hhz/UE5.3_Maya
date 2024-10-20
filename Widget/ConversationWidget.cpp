// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationWidget.h"
#include "ConversationManager.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"
#include "Engine/World.h"



void UConversationWidget::NativeConstruct()
{
	if (!SpeakerText || !ContentText)
	{
		UE_LOG(LogTemp, Error, TEXT("SpeakerText or ContentText is not valid"));
		return;
	}
	if (!GetGameInstance() || !GetGameInstance()->GetSubsystem<UConversationManager>())
	{
		UE_LOG(LogTemp, Error, TEXT("ConversationManager subsystem is not valid"));
		return;
	}
	GetGameInstance()->GetSubsystem<UConversationManager>()->SetConversationWidget(this);
	SetRenderOpacity(0.f);
}

void UConversationWidget::SetConversation(const FString& Speaker, const FString& Content)
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(ClearHandler);

		SpeakerText->SetText(FText::FromString(Speaker));
		ContentText->SetText(FText::GetEmpty());

		SetRenderOpacity(1.f);

		FullContent = Content;

		GetWorld()->GetTimerManager().SetTimer(WriteHandler, this, &UConversationWidget::SetContentSubstring, 0.05f, true);
	}
}

void UConversationWidget::SetContentSubstring()
{
	ContentText->SetText(FText::FromString(FullContent));
	GetWorld()->GetTimerManager().ClearTimer(WriteHandler); 
	GetWorld()->GetTimerManager().SetTimer(ClearHandler, this, &UConversationWidget::PlayFadeAnim, 2.f, false);
}

void UConversationWidget::PlayFadeAnim()
{
	if (!FadeAnim)
	{
		UE_LOG(LogTemp, Error, TEXT("FadeAnim is not set"));
		return;
	}
	PlayAnimation(FadeAnim);
}