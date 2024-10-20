// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionManager.h"
#include "InteractionWidget.h"
#include "MapInteraction.h"

void UInteractionManager::SetInteraction(bool bVisible)
{
	InteractionWidget->SetInteraction(bVisible);
}

void UInteractionManager::SetMapInteraction(int32 cnt)
{
	MapInteraction->SetMapInteraction(cnt);
}

void UInteractionManager::SetInteractionWidget(UInteractionWidget* Widget)
{
	InteractionWidget = Widget;
}

void UInteractionManager::SetMapInteractionWidget(UMapInteraction* Widget)
{
	MapInteraction = Widget;
}