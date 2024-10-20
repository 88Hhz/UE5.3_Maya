// Fill out your copyright notice in the Description page of Project Settings.


#include "MayaCharacter.h"
#include "MayaPlayerController.h"
#include "CharacterEnumState.h"

#include "MayaGameInstance.h"
#include "ActorInteractionManager.h"
#include "MainWidgetManager.h"
#include "MayaMainWidget.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Kismet/GameplayStatics.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMayaCharacter::AMayaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/MayaDefualt/Character/MayaCharacter/sharunwithlig.sharunwithlig'"));
	if (TempMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	}
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bUsePawnControlRotation = true;

	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm);
	FollowCamera->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 350.0f;

}

// Called when the game starts or when spawned
void AMayaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterCurrentState = ECharacterState::Locomotion;
	UMayaGameInstance* GI = Cast<UMayaGameInstance>(GetGameInstance());
	if (GI)
	{
		MaxHp = GI->PlayerHp;
		CurrentHp = MaxHp;
		MaxMana = GI->PlayerMana;
		CurrentMana = MaxMana;
		MaxStamina = GI->PlayerStamina;
		CurrentStamina = MaxStamina;
	}
	bCanControll = true;
}

// Called every frame
void AMayaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAutoTarget)
	{
		FVector DirectionToBoss = BossActor->GetActorLocation() - GetActorLocation();
		DirectionToBoss.Z = 0; 
		FRotator DesiredRotation = DirectionToBoss.Rotation();
		FRotator CurrentRotation = GetActorRotation();

		// 보스의 방향으로 천천히 회전하도록 보간
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, DeltaTime, 5.0f);
		SetActorRotation(NewRotation);

		// 카메라도 보스 방향으로 함께 회전
		AddControllerYawInput(NewRotation.Yaw - CurrentRotation.Yaw);
	}

	if (bImpulse)
	{
		ElapsedTime += DeltaTime;
		float LerpValue = ElapsedTime * ImpulseValue;

		if (LerpValue >= 1.f)
		{
			SetActorLocation(EndPos);
			ElapsedTime = 0.f;
			bImpulse = !bImpulse;
		}
		else
		{
			CurrentPos = FMath::Lerp(StartPos, EndPos, LerpValue);
			SetActorLocation(CurrentPos, true);
			if (FVector::Distance(CurrentPos, EndPos) < 17.f)
			{
				SetActorLocation(EndPos);
				ElapsedTime = 0.f;
				bImpulse = !bImpulse;
			}
		}
	}

}

/*
// Called to bind functionality to input
void AMayaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/

void AMayaCharacter::Move(const FInputActionValue& Value) 
{

	if (CharacterCurrentState != ECharacterState::Attack && !bIsRoll)
	{
		if (bCanControll)
		{
			const FVector2D MovementVector = Value.Get<FVector2D>();

			FRotator ControlRotation = Controller->GetControlRotation();

			const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(ForwardDirection, MovementVector.Y);

			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(RightDirection, MovementVector.X);

			LastDirection = GetVelocity().GetSafeNormal(); //AddImpulseMovement()
		}
	}
	
}

void AMayaCharacter::Look(const FInputActionValue& Value)
{
	if (!bLockOnLook)
	{
		if (bCanControll)
		{
			const FVector2D LookVector = Value.Get<FVector2D>();

			AddControllerYawInput(LookVector.X);
			AddControllerPitchInput(LookVector.Y);
		}
	}
}

void AMayaCharacter::Jump() 
{
	if (CharacterCurrentState == ECharacterState::Locomotion)
	{
		Super::Jump();
		CharacterCurrentState = ECharacterState::Jump;
	}
}

void AMayaCharacter::Roll()
{
	if (CharacterCurrentState == ECharacterState::Locomotion)
	{
		bIsMoving = GetVelocity().Size() > 100.0f;
		if (!bIsRoll && bIsMoving)
		{
			bIsRoll = true;
			CharacterCurrentState = ECharacterState::Roll;
		}
	}
}

void AMayaCharacter::JumpAttack()
{
	if (CharacterCurrentState == ECharacterState::Jump)
	{
		CharacterCurrentState = ECharacterState::Attack;
		CharacterNextAttack = ECharacterAttack::JumpAttack;
		bLockOnLook = true;
	}
}

void AMayaCharacter::ChargedAttack()
{
	if (CharacterCurrentState == ECharacterState::Locomotion)
	{
		CharacterCurrentState = ECharacterState::Attack;
		CharacterNextAttack = ECharacterAttack::ChargedAttack;
		bLockOnLook = true;
	}
}

void AMayaCharacter::Sprint()
{
	if (CharacterCurrentState != ECharacterState::Attack) {

		if (bIsSprint)
		{
			bIsSprint = false;
			GetCharacterMovement()->MaxWalkSpeed = 350.0f;
		}
		else
		{
			bIsSprint = true;
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		}
	}
}

void AMayaCharacter::DashAttack()
{
	if (CharacterCurrentState == ECharacterState::Locomotion)
	{
		CharacterCurrentState = ECharacterState::Attack;
		CharacterNextAttack = ECharacterAttack::DashAttack;
		bLockOnLook = true;
	}
}

void AMayaCharacter::Attack1()
{
	if (CharacterCurrentState == ECharacterState::Locomotion)
	{
		CharacterCurrentState = ECharacterState::Attack;
		CharacterNextAttack = ECharacterAttack::NormalAttack;
		CharacterCurrentCombo = ECharacterCombo::Combo1;
	}
	else if (CharacterCurrentState == ECharacterState::Attack && CharacterNextAttack == ECharacterAttack::NormalAttack)
	{
		if (!bIsAttack) {
			switch (CharacterCurrentCombo)
			{
			case ECharacterCombo::Combo1:
				bIsSetNextAttack = true;
				CharacterCurrentCombo = ECharacterCombo::Combo2;
				break;

			case ECharacterCombo::Combo2:
				bIsSetNextAttack = true;
				CharacterCurrentCombo = ECharacterCombo::Combo3;
				break;

			case ECharacterCombo::Combo3:
				bIsSetNextAttack = true;
				CharacterCurrentCombo = ECharacterCombo::Combo4;
				break;

			default:
				bIsSetNextAttack = false;
			}
			AddImpulseMovement();
			bIsSetNextAttack = false;
		}
	}
	bLockOnLook = true;
}


void AMayaCharacter::Attack2()
{
	if (CharacterCurrentState == ECharacterState::Locomotion)
	{
		CharacterCurrentState = ECharacterState::Attack;
		CharacterNextAttack = ECharacterAttack::ComboAttack;
		CharacterCurrentCombo = ECharacterCombo::Combo1;
	}
	else if (CharacterCurrentState == ECharacterState::Attack && CharacterNextAttack == ECharacterAttack::ComboAttack)
	{
		if (!bIsAttack) {
			switch (CharacterCurrentCombo)
			{
			case ECharacterCombo::Combo1:
				bIsSetNextAttack = true;
				CharacterCurrentCombo = ECharacterCombo::Combo2;
				break;

			case ECharacterCombo::Combo2:
				bIsSetNextAttack = true;
				CharacterCurrentCombo = ECharacterCombo::Combo3;
				break;

			case ECharacterCombo::Combo3:
				bIsSetNextAttack = true;
				CharacterCurrentCombo = ECharacterCombo::Combo4;
				break;

			default:
				bIsSetNextAttack = false;
			}
			AddImpulseMovement();
			bIsSetNextAttack = false;
		}
	}
	bLockOnLook = true;
}

void AMayaCharacter::AttackManagement()
{
	if (RstCombo)
	{
		CharacterCurrentState = ECharacterState::Locomotion;
		CharacterNextAttack = ECharacterAttack::None;
		CharacterCurrentCombo = ECharacterCombo::None;
		RstCombo = !RstCombo;
		if (!bAutoTarget)
		{
			bLockOnLook = false;
		}
	}
}

void AMayaCharacter::UltimateAttack()
{
	if (CharacterCurrentState == ECharacterState::Locomotion)
	{
		CharacterCurrentState = ECharacterState::Attack;
		CharacterNextAttack = ECharacterAttack::UltimateAttack;
	}
}

void AMayaCharacter::SlashSkill()
{
	if (CharacterCurrentState == ECharacterState::Locomotion)
	{
		CharacterCurrentState = ECharacterState::Attack;
		CharacterNextAttack = ECharacterAttack::SlashAttack;
	}
}

void AMayaCharacter::AutoTargetBoss()
{
	if (!BossActor)
	{
		BossActor = GetGameInstance()->GetSubsystem<UActorInteractionManager>()->GetBoss();
	}
	else
	{
		if (!bAutoTarget)
		{
			bLockOnLook = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
		}
		else
		{
			bLockOnLook = false;
			GetCharacterMovement()->bOrientRotationToMovement = true;
			GetCharacterMovement()->bUseControllerDesiredRotation = false;
		}
		bAutoTarget = !bAutoTarget;
	}
}

void AMayaCharacter::AddImpulseMovement()
{
	if (CharacterCurrentState == ECharacterState::Roll)
	{
		if (!bIsSprint)
		{
			StartPos = GetActorLocation();
			EndPos = GetActorLocation() + LastDirection * 250.f;
		}
		else
		{
			StartPos = GetActorLocation();
			EndPos = GetActorLocation() + LastDirection * 350.f;
		}
		bImpulse = true;
	}
	if (CharacterCurrentState == ECharacterState::Attack)
	{
		if (CharacterNextAttack == ECharacterAttack::NormalAttack || CharacterNextAttack == ECharacterAttack::ComboAttack)
		{
			StartPos = GetActorLocation();
			EndPos = GetActorLocation() + LastDirection * 100.f;
		}
		else
		{
			StartPos = GetActorLocation();
			EndPos = GetActorLocation() + LastDirection * 170.f;
		}
		bImpulse = true;
	}
}

float AMayaCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Damage > 0)
	{
		CurrentHp = FMath::Clamp((CurrentHp - Damage), 0.f, MaxHp);
		if (!MainWidget)
		{
			MainWidget = GetGameInstance()->GetSubsystem<UMainWidgetManager>()->GetMainWidget();
		}
		MainWidget->SetHpPercent(CurrentHp / MaxHp);

		if (CurrentHp <= 0)
		{
			CharacterCurrentState = ECharacterState::Dead;
			bCanControll = false;
			AMayaPlayerController* MayaController = Cast<AMayaPlayerController>(GetController());
			if (MayaController)
			{
				MayaController->GameoverUISystem();
			}
		}
	}
	return Damage;
}




