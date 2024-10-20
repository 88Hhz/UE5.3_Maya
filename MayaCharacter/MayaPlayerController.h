// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MayaPlayerController.generated.h"

class AMayaGameModeBase;
class AMayaHUD;
class UMainMenuWidget;
/**
 * 
 */
UCLASS()
class MAYA53_API AMayaPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	AMayaPlayerController();

	UFUNCTION(BlueprintCallable, Category = "UI Function")
	void MenuUISystem();

	UFUNCTION(BlueprintCallable, Category = "UI Function")
	void InGameUISystem();

	UFUNCTION(BlueprintCallable, Category = "UI Function")
	void GameoverUISystem();

	void PauseGame(bool bPause);

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	//FString CurrentLevelName;
	UFUNCTION(BlueprintImplementableEvent, Category = "BPFunction")
	void InteractActor();

private:

	UPROPERTY()
	bool bVisibleSetting = false;

	bool bCanAutoTarget = false;

private:

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputMappingContext* MayaMappingContext;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* JumpAction;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* MoveAction;

	UPROPERTY(VisibleAnyWhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* SprintAction;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* RollAction;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* JumpAttackAction;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* AttackAction1;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* AttackAction2;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* SlashSkillAction;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* UltimateAction;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* AutoTargeting;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* ForSkill;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* UISetting;

	UPROPERTY(VisibleAnywhere, Category = "Input", meta = (allowprivateaccess = true))
	class UInputAction* Interaction;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Jump();
	void Sprint();
	void Roll();
	void JumpAttack();
	void ChargedAttack();
	void DashAttack();
	void Attack1();
	void Attack2();
	void SlashSkill();
	void Ultimate();
	void AutoTarget();

};
