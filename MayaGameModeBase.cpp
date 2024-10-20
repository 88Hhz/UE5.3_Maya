// Fill out your copyright notice in the Description page of Project Settings.


#include "MayaGameModeBase.h"
#include "MayaPlayerController.h"
#include "MayaCharacter.h"
#include "MayaHUD.h"

#include "MayaGameInstance.h"
#include "QuestManager.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/UserWidget.h"

AMayaGameModeBase::AMayaGameModeBase()
{
	PlayerControllerClass = AMayaPlayerController::StaticClass();
	DefaultPawnClass = AMayaCharacter::StaticClass();
	HUDClass = AMayaHUD::StaticClass();
}

void AMayaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		CurrentLevelName = GetWorld()->GetMapName();
		CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		UMayaGameInstance* GI = Cast<UMayaGameInstance>(GetGameInstance());
		if (GI)
		{
			GI->CurrentLevelName = CurrentLevelName;
			UKismetSystemLibrary::PrintString(this, (TEXT("%s"), *GI->CurrentLevelName));
			
		}

		if (CurrentLevelName == "Maya")
		{
			if (GI->bIsRetry) // 사망 후 재도전 시
			{
				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
				if (PlayerController && PlayerController->GetPawn())
				{
					APawn* Player = PlayerController->GetPawn();
					FVector SpawnLocation = FVector(-167984.971604f, 25.313155f, -6048.371452f);
					FRotator SpawnRotation = FRotator(0.f, 60.f, 0.f);
					Player->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
				}
			}
			else //Default
			{
				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
				if (PlayerController && PlayerController->GetPawn())
				{
					APawn* Player = PlayerController->GetPawn();
					FVector SpawnLocation = FVector(-154124.740887f, -30437.198955f, -2476.427924f);
					FRotator SpawnRotation = FRotator(0.f, 90.f, 0.f);
					Player->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
				}
			}
		}
		else if (CurrentLevelName == "TroonBossRoom")
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController && PlayerController->GetPawn())
			{
				APawn* Player = PlayerController->GetPawn();
				FVector SpawnLocation = FVector(-168516.533095f, 1608.635775f, -6588.350457f);
				FRotator SpawnRotation = FRotator(0.f, 125.f, 0.f);
				Player->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
			}
		}
		else if (CurrentLevelName == "To_Exil")
		{
			if (GI->bIsRetry) // 사망 후 재도전 시
			{
				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
				if (PlayerController && PlayerController->GetPawn())
				{
					APawn* Player = PlayerController->GetPawn();
					FVector SpawnLocation = FVector(-158006.14891f, 28252.846792f, 13281.807931f);
					FRotator SpawnRotation = FRotator(0.f, 60.f, 0.f);
					Player->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
				}
			}
			else //Default
			{
				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
				if (PlayerController && PlayerController->GetPawn())
				{
					APawn* Player = PlayerController->GetPawn();
					FVector SpawnLocation = FVector(-163024.432181f, 15674.547221f, -12308.315048f);
					FRotator SpawnRotation = FRotator(0.f, 90.f, 0.f);
					Player->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
				}
			}
		}
	}
}

void AMayaGameModeBase::ChangeLevel(const FString& LevelName)
{
	UMayaGameInstance* GI = Cast<UMayaGameInstance>(GetGameInstance());
	if (GI)
	{
		if (LevelName == "MainMenu")
		{
			GI->RstGameInstance();
		}
		else if (GI->bIsRetry)
		{
			GI->RstCharacterStats();
		}
		else
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController)
			{
				AMayaCharacter* Player = Cast<AMayaCharacter>(PlayerController->GetPawn());
				if (Player)
				{
					GI->SaveCharacterStats(Player->CurrentHp, Player->CurrentMana, Player->CurrentStamina);
				}

			}
		}
	}
	if (GetWorld())
	{
		UGameplayStatics::OpenLevel(GetWorld(), *LevelName);
	}
	
}

void AMayaGameModeBase::PauseGame(bool bPause)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		AMayaPlayerController* MayaController = Cast<AMayaPlayerController>(PlayerController);
		if (MayaController)
		{
			MayaController->PauseGame(bPause);
		}
	}
}



