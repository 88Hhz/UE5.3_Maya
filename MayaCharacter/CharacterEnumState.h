// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterEnumState.generated.h"


UENUM(BlueprintType)
enum class ECharacterState :uint8
{
	Locomotion UMETA(DisplayName = "Locomotion"),
	Attack UMETA(DisplayName = "Attack"),
	Dodge UMETA(DisplayName = "Dodge"),
	Roll UMETA(DisplayName = "Roll"),
	Damaged UMETA(DisplayName = "Damaged"),
	Jump UMETA(DisplayName = "Jump"),
	Dead UMETA(DisplayName = "Dead"),
};

UENUM(BlueprintType)
enum class ECharacterAttack :uint8
{
	None UMETA(DisplayName = "None"),
	NormalAttack UMETA(DisplayName = "NormalAttack"),
	ComboAttack UMETA(DisplayName = "ComboAttack"),
	ChargedAttack UMETA(DisplayName = "ChargedAttack"),
	JumpAttack UMETA(DisplayName = "JumpAttack"),
	DashAttack UMETA(DisplayName = "DashAttack"),
	SlashAttack UMETA(DisplayName = "SlashAttack"),
	UltimateAttack UMETA(DisplayName = "UltimateAttack"),
};

UENUM(BlueprintType)
enum class ECharacterCombo :uint8
{
	None UMETA(DisplayName = "None"),
	Combo1 UMETA(DisplayName = "Combo1"),
	Combo2 UMETA(DisplayName = "Combo2"),
	Combo3 UMETA(DisplayName = "Combo3"),
	Combo4 UMETA(DisplayName = "Combo4"),
};




UCLASS()
class MAYA53_API ACharacterEnumState : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterEnumState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	ECharacterState CharacterState;

	UPROPERTY(EditAnywhere)
	ECharacterAttack CharacterAttack;

	UPROPERTY(EditAnywhere)
	ECharacterCombo CharacterCombo;

};
