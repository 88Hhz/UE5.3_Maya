// Fill out your copyright notice in the Description page of Project Settings.


#include "MayaPlayerController.h"
#include "MayaGameModeBase.h"
#include "MayaCharacter.h"
#include "MayaGameInstance.h"

#include "MayaHUD.h"
#include "ActorInteractionManager.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"




AMayaPlayerController::AMayaPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>DEFAULT_CONTEXT(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/MayaDefualt/Input/IMC_MayaControll.IMC_MayaControll'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_MOVE(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_Move.IA_Move'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_JUMP(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_Jump.IA_Jump'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_JUMPATTACK(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_JumpAttack.IA_JumpAttack'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_LOOK(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_Look.IA_Look'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Sprint(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_Sprint.IA_Sprint'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Roll(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_Roll.IA_Roll'"));


	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SLASHSKILL(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_SlashSkill.IA_SlashSkill'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_ULTIMATESKILL(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_Ultimate.IA_Ultimate'"));

	//Attack_ver.1
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Attackv1(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_Attackv1.IA_Attackv1'"));
	//Attack_ver.2
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Attackv2(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_Attackv2.IA_Attackv2'"));

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_AUTOTARGET(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_AutoTarget.IA_AutoTarget'"));

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Skill(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_Skill.IA_Skill'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_UISetting(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_UISetting.IA_UISetting'"));
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Interaction(TEXT("/Script/EnhancedInput.InputAction'/Game/MayaDefualt/Input/Actions/IA_Interaction.IA_Interaction'"));

	

	if (DEFAULT_CONTEXT.Succeeded()) {
		MayaMappingContext = DEFAULT_CONTEXT.Object;
	}
	if (IA_MOVE.Succeeded()) {
		MoveAction = IA_MOVE.Object;
	}
	if (IA_JUMP.Succeeded()) {
		JumpAction = IA_JUMP.Object;
	}
	if (IA_JUMPATTACK.Succeeded()) {
		JumpAttackAction = IA_JUMPATTACK.Object;
	}
	if (IA_LOOK.Succeeded()) {
		LookAction = IA_LOOK.Object;
	}
	if (IA_Sprint.Succeeded()) {
		SprintAction = IA_Sprint.Object;
	}
	if (IA_Roll.Succeeded()) {
		RollAction = IA_Roll.Object;
	}


	if (IA_SLASHSKILL.Succeeded())
	{
		SlashSkillAction = IA_SLASHSKILL.Object;
	}
	if (IA_ULTIMATESKILL.Succeeded())
	{
		UltimateAction = IA_ULTIMATESKILL.Object;
	}


	if (IA_Attackv1.Succeeded()) {
		AttackAction1 = IA_Attackv1.Object;
	}
	if (IA_Attackv2.Succeeded()) {
		AttackAction2 = IA_Attackv2.Object;
	}

	if (IA_AUTOTARGET.Succeeded())
	{
		AutoTargeting = IA_AUTOTARGET.Object;
	}
	if (IA_Skill.Succeeded())
	{
		ForSkill = IA_Skill.Object;
	}
	if (IA_UISetting.Succeeded())
	{
		UISetting = IA_UISetting.Object;
	}
	if (IA_Interaction.Succeeded())
	{
		Interaction = IA_Interaction.Object;
	}
}


void AMayaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (MayaMappingContext)
		{
			SubSystem->AddMappingContext(MayaMappingContext, 0);
		}
	}

	UMayaGameInstance* GI = Cast<UMayaGameInstance>(GetGameInstance());
	if (GI)
	{
		if (GI->CurrentLevelName == "MainMenu")
		{
			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
		}
		else
		{
			SetInputMode(FInputModeGameOnly());
			bShowMouseCursor = false;
			if ((GI->CurrentLevelName == "TroonBossRoom") || (GI->CurrentLevelName == "ExilBossRoom"))
			{
				bCanAutoTarget = true;
			}
			else
			{
				bCanAutoTarget = false;
			}
		}
		
	}
	bVisibleSetting = false;
}


void AMayaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMayaPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMayaPlayerController::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMayaPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAttackAction, ETriggerEvent::Triggered, this, &AMayaPlayerController::JumpAttack);
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &AMayaPlayerController::Roll);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMayaPlayerController::Sprint);

		EnhancedInputComponent->BindAction(SlashSkillAction, ETriggerEvent::Triggered, this, &AMayaPlayerController::SlashSkill);
		EnhancedInputComponent->BindAction(UltimateAction, ETriggerEvent::Triggered, this, &AMayaPlayerController::Ultimate);

		EnhancedInputComponent->BindAction(AttackAction1, ETriggerEvent::Canceled, this, &AMayaPlayerController::Attack1);
		EnhancedInputComponent->BindAction(AttackAction1, ETriggerEvent::Completed, this, &AMayaPlayerController::ChargedAttack);

		EnhancedInputComponent->BindAction(AttackAction2, ETriggerEvent::Canceled, this, &AMayaPlayerController::Attack2);
		EnhancedInputComponent->BindAction(AttackAction2, ETriggerEvent::Completed, this, &AMayaPlayerController::DashAttack);

		EnhancedInputComponent->BindAction(AutoTargeting, ETriggerEvent::Completed, this, &AMayaPlayerController::AutoTarget);

		EnhancedInputComponent->BindAction(UISetting, ETriggerEvent::Triggered, this, &AMayaPlayerController::InGameUISystem);
		EnhancedInputComponent->BindAction(Interaction, ETriggerEvent::Triggered, this, &AMayaPlayerController::InteractActor);
	}
}

void AMayaPlayerController::MenuUISystem()
{
	AMayaHUD* MayaHUD = Cast<AMayaHUD>(GetHUD());
	if (MayaHUD)
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		MayaHUD->ChangeMenuWidget();
	}
	
}

void AMayaPlayerController::InGameUISystem()
{
	AMayaHUD* MayaHUD = Cast<AMayaHUD>(GetHUD());
	if (MayaHUD)
	{
		if (!bVisibleSetting)
		{
			bShowMouseCursor = true;
			SetInputMode(FInputModeGameAndUI());
			PauseGame(true);
		}
		else
		{
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
			PauseGame(false);
		}
		bVisibleSetting = !bVisibleSetting;
		MayaHUD->ChangeMainWidget();
	}
}

void AMayaPlayerController::PauseGame(bool bPause)
{
	if (bPause)
	{
		SetPause(true);
	}
	else
	{
		SetPause(false);
	}
}

void AMayaPlayerController::GameoverUISystem()
{
	AMayaHUD* MayaHUD = Cast<AMayaHUD>(GetHUD());
	if (MayaHUD)
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		MayaHUD->ChangeGameoverWidget();
	}
}

void AMayaPlayerController::Move(const FInputActionValue& Value)
{
	if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
		ControlledCharacter->Move(Value);
	}
}

void AMayaPlayerController::Look(const FInputActionValue& Value)
{
	if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
		ControlledCharacter->Look(Value);
	}
}

void AMayaPlayerController::Jump()
{
	if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
		ControlledCharacter->Jump();
	}
}


void AMayaPlayerController::Roll()
{
	if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
		ControlledCharacter->Roll();
	}
}

void AMayaPlayerController::JumpAttack()
{
	if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
		ControlledCharacter->JumpAttack();
	}
}


void AMayaPlayerController::ChargedAttack()
{
	if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
		ControlledCharacter->ChargedAttack();
	}
}

void AMayaPlayerController::Sprint()
{
	if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
		ControlledCharacter->Sprint();
	}
}

void AMayaPlayerController::DashAttack()
{
	if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
		ControlledCharacter->DashAttack();
	}
}

void AMayaPlayerController::Attack1()
{
	if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
		ControlledCharacter->Attack1();
	}
}

void AMayaPlayerController::Attack2()
{
	if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
		ControlledCharacter->Attack2();
	}
}

void AMayaPlayerController::SlashSkill()
{
	if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
		ControlledCharacter->SlashSkill();
	}
}

void AMayaPlayerController::Ultimate()
{
	if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
		ControlledCharacter->UltimateAttack();
	}
}

void AMayaPlayerController::AutoTarget()
{
	if (bCanAutoTarget)
	{
		if (AMayaCharacter* ControlledCharacter = Cast<AMayaCharacter>(GetPawn())) {
			ControlledCharacter->AutoTargetBoss();
		}
	}
}