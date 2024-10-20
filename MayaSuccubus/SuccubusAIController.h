// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SuccubusAIController.generated.h"

/**
 * 
 */
UCLASS()
class MAYA53_API ASuccubusAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	ASuccubusAIController();
	virtual void OnPossess(APawn* InPawn) override;

	static const FName Key_State;
	static const FName Key_Attack;
	static const FName Key_Fly;
	static const FName Key_SwordEquip;
	static const FName Key_Target;
	static const FName Key_Distance;
	static const FName Key_HpPercent;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BTAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBlackboardData* BBAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Comp", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Comp", meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* BlackboardComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
