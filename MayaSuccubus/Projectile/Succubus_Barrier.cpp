// Fill out your copyright notice in the Description page of Project Settings.


#include "Succubus_Barrier.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ASuccubus_Barrier::ASuccubus_Barrier()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(StaticMesh);
	SphereCollision->InitSphereRadius(256.f);


	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Niagara(TEXT("/Script/Niagara.NiagaraSystem'/Game/MayaDefualt/Succubus/Projectile/NS_Blood_Magic_Shield_RE.NS_Blood_Magic_Shield_RE'"));
	if (Niagara.Succeeded())
	{
		NSParticle = Niagara.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Niagara2(TEXT("/Script/Niagara.NiagaraSystem'/Game/Blood_Magic/VFX_Niagara/NS_Blood_Magic_Shield_Splash.NS_Blood_Magic_Shield_Splash'"));
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

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ASuccubus_Barrier::OnOverlapBegin);
}

void ASuccubus_Barrier::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASuccubus_Barrier::ActivateNiagara, 2.0f, false);
}

void ASuccubus_Barrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASuccubus_Barrier::ActivateNiagara()
{
	// Niagara2 시스템 활성화
	if (NSComponent2 && !NSComponent2->IsActive())
	{
		SetActorScale3D(GetActorScale3D() * 2.f);
		NSComponent2->Activate();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASuccubus_Barrier::DestroyProjectile, 2.0f, false);
	}

}


void ASuccubus_Barrier::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 100.f, NULL, NULL, NULL);
	}
}