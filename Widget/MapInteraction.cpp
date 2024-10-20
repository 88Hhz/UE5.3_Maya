// Fill out your copyright notice in the Description page of Project Settings.


#include "MapInteraction.h"
#include "InteractionManager.h"
#include "Components/Image.h"
#include "TimerManager.h"

void UMapInteraction::NativeConstruct()
{
	Super::NativeConstruct();

	if (!MapNameImage || !MapFadeIn || !MapFadeOut)
	{
		UE_LOG(LogTemp, Error, TEXT("MapInteraction components are not valid"));
		return;
	}
	if (!GetGameInstance() || !GetGameInstance()->GetSubsystem<UInteractionManager>())
	{
		UE_LOG(LogTemp, Error, TEXT("Map GameInstance is not valid"));
	}
	GetGameInstance()->GetSubsystem<UInteractionManager>()->SetMapInteractionWidget(this);
	SetRenderOpacity(0.f);
	MapNameImage->SetVisibility(ESlateVisibility::Hidden);
	MapNameImage2->SetVisibility(ESlateVisibility::Hidden);
	MapNameImage3->SetVisibility(ESlateVisibility::Hidden);

}

void UMapInteraction::SetMapInteraction(int32 cnt)
{
	if (cnt == 0)
	{
		MapNameImage->SetVisibility(ESlateVisibility::Visible);
		MapNameImage2->SetVisibility(ESlateVisibility::Hidden);
		MapNameImage3->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (cnt == 1)
	{
		MapNameImage->SetVisibility(ESlateVisibility::Hidden);
		MapNameImage2->SetVisibility(ESlateVisibility::Visible);
		MapNameImage3->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		MapNameImage->SetVisibility(ESlateVisibility::Hidden);
		MapNameImage2->SetVisibility(ESlateVisibility::Hidden);
		MapNameImage3->SetVisibility(ESlateVisibility::Visible);
	}
	SetRenderOpacity(1.f);
	PlayFadeIn();
}

void UMapInteraction::PlayFadeIn()
{
	if (!MapFadeIn)
	{
		return;
	}
	PlayAnimation(MapFadeIn);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMapInteraction::PlayFadeOut, 2.5f, false);
}

void UMapInteraction::PlayFadeOut()
{
	if (!MapFadeOut)
	{
		return;
	}
	PlayAnimation(MapFadeOut);
}