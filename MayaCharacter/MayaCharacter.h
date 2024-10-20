// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "CharacterEnumState.h"
#include "MayaCharacter.generated.h"


class UMayaMainWidget;

UCLASS()
class MAYA53_API AMayaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMayaCharacter();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//States
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ECharacterState CharacterCurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ECharacterAttack CharacterNextAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ECharacterCombo CharacterCurrentCombo;

	//State Boolean
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	bool bIsRoll = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	bool bIsMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	bool bIsSetNextAttack = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	bool RstCombo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	bool bIsAttack = false;

	//Character Stats
	

	//Function for AnimNotify
	UFUNCTION(BlueprintCallable, Category = "CustomEvent")
	void AttackManagement();

	UFUNCTION(BlueprintCallable, Category = "CustomEvent")
	void AddImpulseMovement();

	//AddImpulseMovement() Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	float ImpulseValue = 5.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentHp;
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentMana;
	float MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentStamina;
	float MaxStamina;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//AddImpulseMovement() Variables
	UPROPERTY()
	FVector Direction;

	UPROPERTY(VisibleAnywhere, Category = "Variable")
	FVector LastDirection;

	FVector StartPos;
	FVector CurrentPos;
	FVector EndPos;

	float ElapsedTime = 0.f;
	bool bImpulse = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variable")
	bool bCanControll;


private:
	//Camera
	UPROPERTY(EditAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnyWhere, Category = "Camera")
	class UCameraComponent* FollowCamera;

	//State Boolean
	UPROPERTY(VisibleAnywhere, Category = "Variable")
	bool bIsSprint = false;

	UPROPERTY(VisibleAnywhere, Category = "Variable")
	bool bAutoTarget = false;

	UPROPERTY(VisibleAnywhere, Category = "Variable")
	bool bLockOnLook = false;

	UPROPERTY()
	AActor* BossActor;

	UPROPERTY()
	UMayaMainWidget* MainWidget;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	//Controller Functions
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);

	void Jump() override;
	void Sprint();
	void Roll();
	void JumpAttack();
	void ChargedAttack();
	void DashAttack();
	void Attack1();
	void Attack2();
	void SlashSkill();
	void UltimateAttack();
	void AutoTargetBoss();
};
