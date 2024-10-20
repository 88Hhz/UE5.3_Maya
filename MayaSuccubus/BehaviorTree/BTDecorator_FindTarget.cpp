// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_FindTarget.h"
#include "MayaSuccubus.h"
#include "SuccubusAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_FindTarget::UBTDecorator_FindTarget()
{
	NodeName = TEXT("FindTargetObject");
}

bool UBTDecorator_FindTarget::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!Pawn)
	{
		return false;
	}

	AMayaSuccubus* MayaSuccubus = Cast<AMayaSuccubus>(Pawn);
	if (!MayaSuccubus)
	{
		return false;
	}

	AActor* TargetActor = MayaSuccubus->Target;
	if (!TargetActor)
	{
		return false;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASuccubusAIController::Key_Target, TargetActor);

	return true;
}


