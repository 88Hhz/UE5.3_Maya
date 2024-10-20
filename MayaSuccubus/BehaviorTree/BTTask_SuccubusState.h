// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SuccubusEnum.h"
#include "BTTask_SuccubusState.generated.h"

/**
 * 
 */
UCLASS()
class MAYA53_API UBTTask_SuccubusState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SuccubusState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	ESuccubusState NextState;

};
