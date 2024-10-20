// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SuccubusEnum.generated.h"


UENUM(BlueprintType)
enum class ESuccubusState :uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Locomotion UMETA(DisplayName = "Locomotion"),
	Jump UMETA(DisplayName = "Jump"),
	FlyStart UMETA(DisplayName = "FlyStart"),
	Fly UMETA(DisplayName = "Fly"),
	FlyFinish UMETA(DisplayName = "FlyFinish"),
	Dash UMETA(DisplayName = "Dash"),
	EquipSword UMETA(DisplayName = "EquipSword"),
	UnequipSword UMETA(DisplayName = "UnequipSword"),
	Attack UMETA(DisplayName = "Attack"),
	Damaged UMETA(DisplayName = "Damaged"),
	Dead UMETA(DisplayName = "Dead"),
};

UENUM(BlueprintType)
enum class ESuccubusAttack :uint8
{
	None UMETA(DisplayName = "None"),
	Melee UMETA(DisplayName = "Melee"),
	Beam UMETA(DisplayName = "Beam"),
	Meteor UMETA(DisplayName = "Meteor"),
	Slash UMETA(DisplayName = "Slash"),
	Circle UMETA(DisplayName = "Circle"),
	Wall UMETA(DisplayName = "Wall"),
	Barrier UMETA(DisplayName = "Barrier"),
};





UCLASS()
class MAYA53_API ASuccubusEnum : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuccubusEnum();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
