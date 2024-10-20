// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SuccubusEnum.h"
#include "Succubus_Projectile_Base.h"
#include "Succubus_Meteor.h"
#include "Succubus_Dash.h"
#include "Succubus_Circle.h"

#include "MayaSuccubus.generated.h"

class UBossHpWidget;

UCLASS()
class MAYA53_API AMayaSuccubus : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMayaSuccubus();


	//Boss State
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ESuccubusState SuccubusCurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ESuccubusAttack SuccubusNextAttack;

	UFUNCTION(BlueprintCallable, Category = "Function")
	void SetSuccubusState(ESuccubusState State, ESuccubusAttack Attack, bool bIsFlying, bool bIsEquip);

	//Instigator
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actor")
	AActor* Target;	

	//Boss Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	float MaxHp = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	float CurrentHp;

	//Boss State Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bIsFly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bIsSwordEquip = false;

	UFUNCTION(BlueprintCallable, Category = "Function")
	void EquipSwordSystem(bool bIsEquip);

	UFUNCTION(BlueprintCallable, Category = "Function")
	void SpawnBeam();

	UFUNCTION(BlueprintCallable, Category = "Function")
	void SpawnMeteor();

	UFUNCTION(BlueprintCallable, Category = "Function")
	void MeteorThrow();

	UFUNCTION(BlueprintCallable, Category = "Function")
	void SpawnDash();

	UFUNCTION(BlueprintCallable, Category = "Function")
	void SpawnWall();

	UFUNCTION(BlueprintCallable, Category = "Function")
	void SpawnBarrier();

	UFUNCTION(BlueprintCallable, Category = "Function")
	void SpawnCircle();

	UFUNCTION(BlueprintCallable, Category = "Function")
	void DestroySpawnedActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPClass")
	UClass* BPSword;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor")
	AActor* SuccubusSword;

	//Projectiles
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPClass")
	UClass* BPBeam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPClass")
	UClass* BPMeteor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPClass")
	UClass* BPDash;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPClass")
	UClass* BPWall;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPClass")
	UClass* BPBarrier;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BPClass")
	UClass* BPCircle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectileClass")
	ASuccubus_Projectile_Base* TempProjectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectileClass")
	ASuccubus_Meteor* TempMeteor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectileClass")
	ASuccubus_Dash* TempDash;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectileClass")
	ASuccubus_Circle* TempCircle;
	//Widget
	UPROPERTY(EditDefaultsOnly, Category = "WidgetBP")
	TSubclassOf<UBossHpWidget> WBP_BossHpWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WidgetBP")
	UBossHpWidget* BossWidget;


	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
