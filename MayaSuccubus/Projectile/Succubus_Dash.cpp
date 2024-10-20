// Fill out your copyright notice in the Description page of Project Settings.


#include "Succubus_Dash.h"
#include "Kismet/GameplayStatics.h"

ASuccubus_Dash::ASuccubus_Dash()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Niagara(TEXT("/Script/Niagara.NiagaraSystem'/Game/Blood_Magic/VFX_Niagara/NS_Blood_Magic_Dash.NS_Blood_Magic_Dash'"));
	if (Niagara.Succeeded())
	{
		NSParticle = Niagara.Object;
	}

	NSComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NSComponent->SetupAttachment(StaticMesh);
	if (NSParticle)
	{
		NSComponent->SetAsset(NSParticle);
		NSComponent->bAutoActivate = true;
	}
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASuccubus_Dash::OnOverlapBegin);
}

void ASuccubus_Dash::BeginPlay()
{
	Super::BeginPlay();

}

void ASuccubus_Dash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsFollow)
	{
		MoveTowardTarget(DeltaTime);
	}
}

void ASuccubus_Dash::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 100.f, NULL, NULL, NULL);
	}
}

void ASuccubus_Dash::MoveTowardTarget(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + Direction * 1500.f * DeltaTime;
	SetActorLocation(NewLocation);

	if (FVector::Dist(NewLocation, TargetLocation) <= 10.f)
	{
		bIsFollow = false;
		DestroyProjectile();
	}
}