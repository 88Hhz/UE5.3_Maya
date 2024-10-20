// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InteractionWidget.h"
#include "InteractionManager.h"
#include "Components/Image.h"


void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!FadeAnim || !Image_G)
	{
		UE_LOG(LogTemp, Error, TEXT("Interaction components are not valid"));
		return;
	}
	if (!GetGameInstance() || !GetGameInstance()->GetSubsystem<UInteractionManager>())
	{
		UE_LOG(LogTemp, Error, TEXT("InteractionManager is not valid"));
		return;
	}
	GetGameInstance()->GetSubsystem<UInteractionManager>()->SetInteractionWidget(this);
	SetRenderOpacity(0.f);
}


void UInteractionWidget::SetInteraction(bool bVisible)
{
	if (bVisible)
	{
		SetRenderOpacity(1.f);
		PlayAnim(true);
	}
	else
	{
		SetRenderOpacity(0.f);
		PlayAnim(false);
	}

}

void UInteractionWidget::PlayAnim(bool bAnim)
{
	if (bAnim)
	{
		PlayAnimation(FadeAnim, 0.f, 0.f);
	}
	else
	{
		StopAnimation(FadeAnim);
	}
}
