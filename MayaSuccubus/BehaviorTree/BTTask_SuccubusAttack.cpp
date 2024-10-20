// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SuccubusAttack.h"
#include "MayaSuccubus.h"
#include "SuccubusAIController.h"

UBTTask_SuccubusAttack::UBTTask_SuccubusAttack()
{
	NodeName = TEXT("SettingAttack");
}

EBTNodeResult::Type UBTTask_SuccubusAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	AMayaSuccubus* MayaSuccubus = Cast<AMayaSuccubus>(Pawn);
	if (!MayaSuccubus)
	{
		return EBTNodeResult::Failed;
	}

	switch (NextAttack)
	{
	case ESuccubusAttack::Melee:
		MayaSuccubus->SetSuccubusState(ESuccubusState::Attack, ESuccubusAttack::Melee, false, false);
		break;
	case ESuccubusAttack::Beam:
		MayaSuccubus->SetSuccubusState(ESuccubusState::Attack, ESuccubusAttack::Beam, false, false);
		break;
	case ESuccubusAttack::Meteor:
		MayaSuccubus->SetSuccubusState(ESuccubusState::Attack, ESuccubusAttack::Meteor, false, false);
		break;
	case ESuccubusAttack::Slash:
		MayaSuccubus->SetSuccubusState(ESuccubusState::Attack, ESuccubusAttack::Slash, false, true);
		break;
	case ESuccubusAttack::Circle:
		MayaSuccubus->SetSuccubusState(ESuccubusState::Attack, ESuccubusAttack::Circle, false, true);
		break;
	case ESuccubusAttack::Wall:
		MayaSuccubus->SetSuccubusState(ESuccubusState::Attack, ESuccubusAttack::Wall, false, false);
		MayaSuccubus->SpawnWall();
		break;
	case ESuccubusAttack::Barrier:
		MayaSuccubus->SetSuccubusState(ESuccubusState::Attack, ESuccubusAttack::Barrier, false, false);
		MayaSuccubus->SpawnBarrier();
		break;
	}
	return EBTNodeResult::Succeeded;
}