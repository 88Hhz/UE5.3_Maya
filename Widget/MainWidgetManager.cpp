// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainWidgetManager.h"
#include "MayaMainWidget.h"


void UMainWidgetManager::SetMainWidget(UMayaMainWidget* Widget)
{
	MayaMainWidget = Widget;
}

void UMainWidgetManager::SetHpPercent(float InPercent)
{
	MayaMainWidget->SetHpPercent(InPercent);
}

void UMainWidgetManager::SetStaminaPercent(float InPercent)
{
	MayaMainWidget->SetStaminaPercent(InPercent);
}

void UMainWidgetManager::SetManaPercent(float InPercent)
{
	MayaMainWidget->SetManaPercent(InPercent);
}