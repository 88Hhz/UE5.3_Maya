// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MayaMainWidget.h"
#include "MainWidgetManager.h"
#include "Components/ProgressBar.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void UMayaMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Hp_Bar || !Hp_BackBar || !Mana_Bar || !Mana_BackBar || !Stamina_Bar || !Stamina_BackBar)
	{
		UE_LOG(LogTemp, Error, TEXT("MainWidget Components are not valid"));
		return;
	}
	GetGameInstance()->GetSubsystem<UMainWidgetManager>()->SetMainWidget(this);
}


void UMayaMainWidget::SetHpPercent(float InPercent)
{
	TargetHp = InPercent;
	Hp_Bar->SetPercent(TargetHp);
	Hp_Lerp();
}

void UMayaMainWidget::SetStaminaPercent(float InPercent)
{
	TargetStamina = InPercent;
	Stamina_Bar->SetPercent(TargetStamina);
	Stamina_Lerp();
}

void UMayaMainWidget::SetManaPercent(float InPercent)
{
	TargetMana = InPercent;
	Mana_Bar->SetPercent(TargetMana);
	Mana_Lerp();
}

void UMayaMainWidget::Hp_Lerp()
{
	float BackBar = Hp_BackBar->GetPercent();

	if (BackBar - TargetHp > 0.0001f)
	{
		float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this) * 1.5f;
		Hp_BackBar->SetPercent(FMath::Lerp(BackBar, TargetHp, DeltaTime));
		GetWorld()->GetTimerManager().SetTimer(FHpHandle, this, &UMayaMainWidget::Hp_Lerp, DeltaTime, false);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(FHpHandle);
	}
}

void UMayaMainWidget::Stamina_Lerp()
{
	float BackBar = Stamina_BackBar->GetPercent();

	if (BackBar - TargetStamina > 0.0001f)
	{
		float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this) * 1.5f;
		Stamina_BackBar->SetPercent(FMath::Lerp(BackBar, TargetStamina, DeltaTime));
		GetWorld()->GetTimerManager().SetTimer(FStaminaHandle, this, &UMayaMainWidget::Stamina_Lerp, DeltaTime, false);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(FStaminaHandle);
	}
}

void UMayaMainWidget::Mana_Lerp()
{
	float BackBar = Mana_BackBar->GetPercent();

	if (BackBar - TargetMana > 0.0001f)
	{
		float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this) * 1.5f;
		Mana_BackBar->SetPercent(FMath::Lerp(BackBar, TargetMana, DeltaTime));
		GetWorld()->GetTimerManager().SetTimer(FManaHandle, this, &UMayaMainWidget::Mana_Lerp, DeltaTime, false);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(FManaHandle);
	}
}
