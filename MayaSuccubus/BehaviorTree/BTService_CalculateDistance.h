// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CalculateDistance.generated.h"

/**
 * 
 */
UCLASS()
class MAYA53_API UBTService_CalculateDistance : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_CalculateDistance();

	float Dis;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
