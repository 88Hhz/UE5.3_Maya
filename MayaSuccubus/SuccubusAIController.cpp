// Fill out your copyright notice in the Description page of Project Settings.


#include "SuccubusAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"


const FName ASuccubusAIController::Key_State(TEXT("CurrentState"));
const FName ASuccubusAIController::Key_Attack(TEXT("NextAttack"));
const FName ASuccubusAIController::Key_Fly(TEXT("IsFly"));
const FName ASuccubusAIController::Key_SwordEquip(TEXT("IsSwordEquip"));
const FName ASuccubusAIController::Key_Target(TEXT("Target"));
const FName ASuccubusAIController::Key_Distance(TEXT("Distance"));
const FName ASuccubusAIController::Key_HpPercent(TEXT("HpPercent"));


ASuccubusAIController::ASuccubusAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/MayaDefualt/Succubus/AI/BT_MayaSuccubus.BT_MayaSuccubus'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Script/AIModule.BlackboardData'/Game/MayaDefualt/Succubus/AI/BB_MayaSuccubus.BB_MayaSuccubus'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

}

void ASuccubusAIController::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(BTAsset))
	{
		RunBehaviorTree(BTAsset);
		BehaviorComp->StartTree(*BTAsset);
	}
}

void ASuccubusAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		BlackboardComp->InitializeBlackboard(*BBAsset);
	}
}

