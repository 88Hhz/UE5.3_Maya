// Fill out your copyright notice in the Description page of Project Settings.


#include "Succubus_Meteor.h"
#include "Kismet/GameplayStatics.h"

ASuccubus_Meteor::ASuccubus_Meteor()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(StaticMesh);
	SphereCollision->InitSphereRadius(32.f);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Niagara(TEXT("/Script/Niagara.NiagaraSystem'/Game/Blood_Magic/VFX_Niagara/NS_Blood_Magic_Orb.NS_Blood_Magic_Orb'"));
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

	ProjectileMovement->ProjectileGravityScale = 1.f;
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ASuccubus_Meteor::OnOverlapBegin);
}


void ASuccubus_Meteor::BeginPlay()
{
	Super::BeginPlay();
}


void ASuccubus_Meteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorScale3D(GetActorScale3D() + 0.02f);

	if (bIsThrow)
	{
		ThrowForward(DeltaTime);
	}
}

void ASuccubus_Meteor::ThrowForward(float DeltaTime)
{
	bIsThrow = true;
	float Speed = 1000.f;
	FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * Speed * DeltaTime) + (GetActorUpVector() * -500.f * DeltaTime);

	SetActorLocation(NewLocation);
}

void ASuccubus_Meteor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 200.f, NULL, NULL, NULL);
	}
}

