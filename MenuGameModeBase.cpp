// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameModeBase.h"
#include "MayaPlayerController.h"
#include "MayaHUD.h"

#include "MayaGameInstance.h"

#include "Kismet/GameplayStatics.h"

AMenuGameModeBase::AMenuGameModeBase()
{
	PlayerControllerClass = AMayaPlayerController::StaticClass();
	HUDClass = AMayaHUD::StaticClass();
}


void AMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();


	if (GetWorld())
	{
		FString CurrentLevelName = GetWorld()->GetMapName();
		CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		UMayaGameInstance* GI = Cast<UMayaGameInstance>(GetGameInstance());
		if (GI)
		{
			GI->CurrentLevelName = CurrentLevelName;
		}

		if (CurrentLevelName == "MainMenu")
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController && PlayerController->GetPawn())
			{
				APawn* Player = PlayerController->GetPawn();
				FVector SpawnLocation = FVector(-154433.359694f, -25858.632634f, 1698.539476f);
				FRotator SpawnRotation = FRotator(0.f, 102.800003f, -6.2f);
				Player->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
			}

		}
	}
}