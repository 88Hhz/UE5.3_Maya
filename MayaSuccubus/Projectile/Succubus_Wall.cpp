// Fill out your copyright notice in the Description page of Project Settings.


#include "Succubus_Wall.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ASuccubus_Wall::ASuccubus_Wall()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Niagara(TEXT("/Script/Niagara.NiagaraSystem'/Game/Blood_Magic/VFX_Niagara/NS_Blood_Magic_Marker.NS_Blood_Magic_Marker'"));
	if (Niagara.Succeeded())
	{
		NSParticle = Niagara.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Niagara2(TEXT("/Script/Niagara.NiagaraSystem'/Game/Blood_Magic/VFX_Niagara/NS_Blood_Magic_Wall1.NS_Blood_Magic_Wall1'"));
	if (Niagara.Succeeded())
	{
		NSParticle2 = Niagara2.Object;
	}


	NSComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NSComponent->SetupAttachment(StaticMesh);
	if (NSParticle)
	{
		NSComponent->SetAsset(NSParticle);
		NSComponent->bAutoActivate = true;
	}

	NSComponent2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent2"));
	NSComponent2->SetupAttachment(StaticMesh);
	if (NSParticle2)
	{
		NSComponent2->SetAsset(NSParticle2);
		NSComponent2->bAutoActivate = false;
	}

}


void ASuccubus_Wall::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASuccubus_Wall::ActivateNiagara, 1.0f, false);
}

void ASuccubus_Wall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASuccubus_Wall::ActivateNiagara()
{
	// Niagara2 시스템 활성화
	if (NSComponent2 && !NSComponent2->IsActive())
	{
		NSComponent2->Activate();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASuccubus_Wall::DestroyProjectile, 2.0f, false);
	}
}


void ASuccubus_Wall::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 100.f, NULL, NULL, NULL);
	}
}