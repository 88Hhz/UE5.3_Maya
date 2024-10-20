// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SuccubusState.h"
#include "MayaSuccubus.h"
#include "SuccubusAIController.h"

UBTTask_SuccubusState::UBTTask_SuccubusState()
{
	NodeName = TEXT("SetState");
}

EBTNodeResult::Type UBTTask_SuccubusState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	switch (NextState)
	{
	case ESuccubusState::Idle:
		MayaSuccubus->SetSuccubusState(ESuccubusState::Idle, ESuccubusAttack::None, false, false);
		break;

	case ESuccubusState::Locomotion:
		MayaSuccubus->SetSuccubusState(ESuccubusState::Locomotion, ESuccubusAttack::None, false, false);
		break;

	case ESuccubusState::EquipSword:
		MayaSuccubus->SetSuccubusState(ESuccubusState::EquipSword, ESuccubusAttack::None, false, true);
		MayaSuccubus->bIsSwordEquip = true;
		break;

	case ESuccubusState::UnequipSword:
		MayaSuccubus->SetSuccubusState(ESuccubusState::UnequipSword, ESuccubusAttack::None, false, false);
		MayaSuccubus->bIsSwordEquip = false;
		break;

	case ESuccubusState::FlyStart:
		MayaSuccubus->SetSuccubusState(ESuccubusState::FlyStart, ESuccubusAttack::None, false, false);
		break;

	case ESuccubusState::FlyFinish:
		MayaSuccubus->SetSuccubusState(ESuccubusState::FlyFinish, ESuccubusAttack::None, true, false);
		break;

	case ESuccubusState::Dash:
		MayaSuccubus->SetSuccubusState(ESuccubusState::Dash, ESuccubusAttack::None, true, false);
		break;
	}

	return EBTNodeResult::Succeeded;
}