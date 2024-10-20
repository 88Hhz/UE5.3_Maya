// Fill out your copyright notice in the Description page of Project Settings.


#include "Succubus_Circle.h"

#include "Kismet/GameplayStatics.h"


ASuccubus_Circle::ASuccubus_Circle()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Niagara(TEXT("/Script/Niagara.NiagaraSystem'/Game/MayaDefualt/Succubus/Projectile/NS_Blood_Magic_Slash_Re.NS_Blood_Magic_Slash_Re'"));
	if (Niagara.Succeeded())
	{
		NSParticle = Niagara.Object;
	}
	NSComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NSComponent->SetupAttachment(StaticMesh);
	if (NSParticle)
	{
		NSComponent->SetAsset(NSParticle);
		NSComponent->SetRelativeRotation(FRotator(0.f, 0.f, -45.f));
		NSComponent->bAutoActivate = true;
	}
	BoxCollision->SetRelativeRotation(FRotator(0.f, 0.f, -45.f));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASuccubus_Circle::OnOverlapBegin);
}

void ASuccubus_Circle::BeginPlay()
{
	Super::BeginPlay();

}

void ASuccubus_Circle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Speed = 1500.f;
	FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * Speed * DeltaTime);
	SetActorLocation(NewLocation);
}

void ASuccubus_Circle::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 100.f, NULL, NULL, NULL);
	}
}
