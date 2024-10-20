// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ActorInteractionManager.generated.h"

/**
 * 
 */
UCLASS()
class MAYA53_API UActorInteractionManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetAkkatActor(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void SetDoorActor(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void SetBossActor(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AActor* GetAkkat() { return Akkat; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AActor* GetDoor() { return Door; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AActor* GetBoss() { return Boss; }

private:
	UPROPERTY()
	AActor* Akkat;

	UPROPERTY()
	AActor* Door;

	UPROPERTY()
	AActor* Boss;
};
