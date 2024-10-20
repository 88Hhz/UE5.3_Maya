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

	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().ClearTimer(ClearContentHandle);

	SpeakerText->SetText(FText::FromString(Speaker));
	ContentText->SetText(FText::GetEmpty());

	SetRenderOpacity(1.f);

	FullContent = Content;

	GetWorld()->GetTimerManager().SetTimer(TypeWriterTimerHandle, this, &UConversationWidget::SetContentSubstring, 0.05f, true);
}

void UConversationWidget::SetContentSubstring()
{
	/*
	int CurrLength = CurrentContent.Len() + 1;

	// *** Mid는 Substring과 같다. ***
	CurrentContent = FullContent.Mid(0, CurrLength);
	ContentText->SetText(FText::FromString(CurrentContent));
	*/
	ContentText->SetText(FText::FromString(FullContent));
	GetWorld()->GetTimerManager().ClearTimer(TypeWriterTimerHandle); // 타이머 클리어
	GetWorld()->GetTimerManager().SetTimer(ClearContentHandle, this, &UConversationWidget::PlayFadeAnim, 2.f, false);

	/*
	// 끝까지 다 출력했다면
	if (CurrLength == FullContent.Len())
	{
		GetWorld()->GetTimerManager().ClearTimer(TypeWriterTimerHandle); // 타이머 클리어

		// 2초 뒤 페이드아웃 애니메이션 재생
		GetWorld()->GetTimerManager().SetTimer(ClearContentHandle, this, &UConversation::PlayFadeAnim, 2.f, false);
	}
	*/
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