// Fill out your copyright notice in the Description page of Project Settings.


#include "MayaSuccubus.h"
#include "Components/CapsuleComponent.h"
#include "SuccubusAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Succubus_Beam.h"
#include "Succubus_Wall.h"
#include "Succubus_Barrier.h"

#include "MayaGameModeBase.h"
#include "BossHpWidget.h"

#include "UObject/ConstructorHelpers.h"
#include "kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AMayaSuccubus::AMayaSuccubus()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Succubus/Mesh/CustomSkeleton/SK_Succubus_Custom.SK_Succubus_Custom'"));
	if (TempMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	}
	GetCharacterMovement()->MaxWalkSpeed = 130.0f;

	AIControllerClass = ASuccubusAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	static ConstructorHelpers::FObjectFinder<UClass> BpSword(TEXT("/Script/Engine.Blueprint'/Game/MayaDefualt/Succubus/BP_Succubus_Sword.BP_Succubus_Sword_C'"));
	if (BpSword.Object)
	{
		BPSword = (UClass*)BpSword.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> BpClass(TEXT("/Script/Engine.Blueprint'/Game/MayaDefualt/Succubus/Projectile/BP_Succubus_Beam.BP_Succubus_Beam_C'"));
	if (BpClass.Object)
	{
		BPBeam = (UClass*)BpClass.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> BpClass2(TEXT("/Script/Engine.Blueprint'/Game/MayaDefualt/Succubus/Projectile/BP_Succubus_Meteor.BP_Succubus_Meteor_C'"));
	if (BpClass2.Object)
	{
		BPMeteor = (UClass*)BpClass2.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> BpClass3(TEXT("/Script/Engine.Blueprint'/Game/MayaDefualt/Succubus/Projectile/BP_Succubus_Dash.BP_Succubus_Dash_C'"));
	if (BpClass3.Object)
	{
		BPDash = (UClass*)BpClass3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> BpClass4(TEXT("/Script/Engine.Blueprint'/Game/MayaDefualt/Succubus/Projectile/BP_Succubus_Wall.BP_Succubus_Wall_C'"));
	if (BpClass4.Object)
	{
		BPWall = (UClass*)BpClass4.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> BpClass5(TEXT("/Script/Engine.Blueprint'/Game/MayaDefualt/Succubus/Projectile/BP_Succubus_Barrier.BP_Succubus_Barrier_C'"));
	if (BpClass5.Object)
	{
		BPBarrier = (UClass*)BpClass5.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass> BpClass6(TEXT("/Script/Engine.Blueprint'/Game/MayaDefualt/Succubus/Projectile/BP_Succubus_Circle.BP_Succubus_Circle_C'"));
	if (BpClass6.Object)
	{
		BPCircle = (UClass*)BpClass6.Object;
	}
}

// Called when the game starts or when spawned
void AMayaSuccubus::BeginPlay()
{
	Super::BeginPlay();

	SetSuccubusState(ESuccubusState::Idle, ESuccubusAttack::None, false, false);
	
	SetSuccubusState(ESuccubusState::Idle, ESuccubusAttack::None, false, false);

	CurrentHp = MaxHp;

	if (AAIController* AIController = Cast<ASuccubusAIController>(GetController()))
	{
		if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
		{
			BlackboardComp->SetValueAsFloat(ASuccubusAIController::Key_HpPercent, (CurrentHp / MaxHp));
		}
	}

	if (BPSword)
	{
		SuccubusSword = GetWorld()->SpawnActor<AActor>(BPSword, FVector::ZeroVector, FRotator::ZeroRotator);
		if (SuccubusSword)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
			SuccubusSword->AttachToComponent(GetMesh(), AttachmentRules, FName("Hip_Sword_LSocket"));
		}
	}


	if (WBP_BossHpWidget)
	{
		BossWidget = CreateWidget<UBossHpWidget>(GetWorld(), WBP_BossHpWidget);
		BossWidget->AddToViewport(1);
		FString Name = FString(TEXT("카무조츠"));
		BossWidget->SetBossName(Name);
		BossWidget->SetHpPercent(CurrentHp / MaxHp);
		BossWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

// Called every frame
void AMayaSuccubus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMayaSuccubus::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMayaSuccubus::SetSuccubusState(ESuccubusState State, ESuccubusAttack Attack, bool bIsFlying, bool bIsEquip)
{
	if (SuccubusCurrentState != ESuccubusState::Dead)
	{
		SuccubusCurrentState = State;
		SuccubusNextAttack = Attack;
		if (ASuccubusAIController* AIController = Cast<ASuccubusAIController>(GetController()))
		{
			if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
			{
				BlackboardComp->SetValueAsEnum(ASuccubusAIController::Key_State, static_cast<uint8>(State));
				BlackboardComp->SetValueAsEnum(ASuccubusAIController::Key_Attack, static_cast<uint8>(Attack));
				BlackboardComp->SetValueAsBool(ASuccubusAIController::Key_Fly, bIsFlying);
				BlackboardComp->SetValueAsBool(ASuccubusAIController::Key_SwordEquip, bIsEquip);
			}
		}
		if (SuccubusCurrentState == ESuccubusState::Locomotion)
		{
			GetCharacterMovement()->MaxWalkSpeed = 130.0f;
		}
	}
}

void AMayaSuccubus::EquipSwordSystem(bool bIsEquip)
{
	if (SuccubusSword)
	{
		if (bIsEquip)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
			SuccubusSword->AttachToComponent(GetMesh(), AttachmentRules, FName("Sword_RSocket"));
			bIsSwordEquip = true;
			SetSuccubusState(ESuccubusState::Locomotion, ESuccubusAttack::None, false, true);
		}
		else
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
			SuccubusSword->AttachToComponent(GetMesh(), AttachmentRules, FName("Hip_Sword_LSocket"));
			bIsSwordEquip = false;
			SetSuccubusState(ESuccubusState::Locomotion, ESuccubusAttack::None, false, false);
		}
	}
}



void AMayaSuccubus::SpawnBeam()
{
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	FVector AddPos = GetActorForwardVector() * 100.f;
	//TempActor = GetWorld()->SpawnActor<AActor>(BPBeam, SpawnLocation + AddPos, SpawnRotation);

	if (BPBeam)
	{
		TempProjectile = GetWorld()->SpawnActor<ASuccubus_Beam>(BPBeam, SpawnLocation + AddPos, SpawnRotation);
		//TempBeam = GetWorld()->SpawnActor<ASuccubus_Beam>(BeamActor, SpawnLocation + AddPos, SpawnRotation);
	}
}

void AMayaSuccubus::SpawnMeteor()
{
	FVector SpawnLocation = GetActorLocation();
	FVector AddPos = GetActorUpVector() * 300.f;

	if (BPMeteor)
	{
		TempMeteor = GetWorld()->SpawnActor<ASuccubus_Meteor>(BPMeteor, SpawnLocation + AddPos, FRotator(GetActorRotation()));
	}

}
void AMayaSuccubus::MeteorThrow()
{
	TempMeteor->bIsThrow = true;
}


void AMayaSuccubus::SpawnDash()
{
	FVector SpawnLocation = GetActorLocation();

	if (BPDash)
	{
		TempDash = GetWorld()->SpawnActor<ASuccubus_Dash>(BPDash, SpawnLocation, FRotator(GetActorRotation()));
	}
	if (Target)
	{
		FVector TargetLocation = Target->GetActorLocation();
		FVector ForwardVector = GetActorForwardVector();
		FVector EndLocation = TargetLocation + (ForwardVector * 200.f);
		FVector AddPos = FVector(0.f, 0.f, -70.f);

		SetActorLocation(EndLocation);
		TempDash->bIsFollow = true;
		TempDash->TargetLocation = EndLocation + (ForwardVector * 100.f) + AddPos;
	}

}

void AMayaSuccubus::SpawnWall()
{
	FVector SpawnLocation = Target->GetActorLocation();
	FVector AddPos = FVector(0.f, 0.f, -70.f);
	FRotator SpawnRotation = Target->GetActorRotation();

	if (BPWall)
	{
		TempProjectile = GetWorld()->SpawnActor<ASuccubus_Wall>(BPWall, SpawnLocation + AddPos, SpawnRotation);
	}
}

void AMayaSuccubus::SpawnBarrier()
{
	FVector SpawnLocation = GetActorLocation();
	FVector AddPos = FVector(0.f, 0.f, -100.f);
	FRotator SpawnRotation = GetActorRotation();

	if (BPBarrier)
	{
		TempProjectile = GetWorld()->SpawnActor<ASuccubus_Barrier>(BPBarrier, SpawnLocation + AddPos, SpawnRotation);
	}
}

void AMayaSuccubus::SpawnCircle()
{
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	if (BPCircle)
	{
		TempCircle = GetWorld()->SpawnActor<ASuccubus_Circle>(BPCircle, SpawnLocation, SpawnRotation);
	}

}

void AMayaSuccubus::DestroySpawnedActor()
{
	//GetWorld()->DestroyActor(TempActor);

	TempProjectile->DestroyProjectile();
	TempProjectile = nullptr;
}

float AMayaSuccubus::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	CurrentHp = FMath::Clamp((CurrentHp - Damage), 0.f, MaxHp);
	BossWidget->SetHpPercent(CurrentHp / MaxHp);
	if (ASuccubusAIController* AIController = Cast<ASuccubusAIController>(GetController()))
	{
		if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
		{
			BlackboardComp->SetValueAsFloat(ASuccubusAIController::Key_HpPercent, (CurrentHp / MaxHp));
		}
	}
	if (CurrentHp <= 0)
	{
		SetSuccubusState(ESuccubusState::Dead, ESuccubusAttack::None, false, false);
	}
	return Damage;
}