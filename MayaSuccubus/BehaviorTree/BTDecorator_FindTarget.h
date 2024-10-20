// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_FindTarget.generated.h"

/**
 * 
 */
UCLASS()
class MAYA53_API UBTDecorator_FindTarget : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_FindTarget();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
