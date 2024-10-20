// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BossHpWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "MayaGameInstance.h"

#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void UBossHpWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UBossHpWidget::SetBossName(const FString& Name)
{
	BossName->SetText(FText::FromString(Name));
}

void UBossHpWidget::SetHpPercent(float InPercent)
{
	TargetHp = InPercent;
	Hp_Bar->SetPercent(TargetHp);
	Hp_Lerp();
}


void UBossHpWidget::Hp_Lerp()
{
	float BackBar = Hp_BackBar->GetPercent();

	if (BackBar - TargetHp > 0.0001f)
	{
		float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this) * 1.5f;
		Hp_BackBar->SetPercent(FMath::Lerp(BackBar, TargetHp, DeltaTime));
		GetWorld()->GetTimerManager().SetTimer(FHpHandle, this, &UBossHpWidget::Hp_Lerp, DeltaTime, false);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(FHpHandle);
	}
}