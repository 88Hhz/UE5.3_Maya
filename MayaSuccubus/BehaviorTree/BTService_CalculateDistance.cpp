// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CalculateDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MayaSuccubus.h"
#include "SuccubusAIController.h"


UBTService_CalculateDistance::UBTService_CalculateDistance()
{
	NodeName = TEXT("Distance");
	Interval = 1.0f;
}

void UBTService_CalculateDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn)
	{
		Dis = FVector::Distance(Pawn->GetActorLocation(), Pawn->GetInstigator()->GetActorLocation());
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ASuccubusAIController::Key_Distance, Dis);
}

