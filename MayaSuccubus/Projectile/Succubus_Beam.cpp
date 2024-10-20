// Fill out your copyright notice in the Description page of Project Settings.


#include "Succubus_Beam.h"
#include "kismet/GameplayStatics.h"

ASuccubus_Beam::ASuccubus_Beam()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Niagara(TEXT("/Script/Niagara.NiagaraSystem'/Game/Blood_Magic/VFX_Niagara/NS_Blood_Magic_Beam1.NS_Blood_Magic_Beam1'"));
	if (Niagara.Succeeded())
	{
		NSParticle = Niagara.Object;
	}
	BoxCollision->SetRelativeLocation(FVector(425.f, 0.f, 0.f));
	BoxCollision->SetRelativeScale3D(FVector(14.1f, 1.7f, 1.7f));

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASuccubus_Beam::OnOverlapBegin);
}


void ASuccubus_Beam::BeginPlay()
{
	Super::BeginPlay();

	NSComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSParticle, FVector(GetActorLocation()), FRotator(GetActorRotation()));
}


void ASuccubus_Beam::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 150.f, NULL, NULL, NULL);
	}
}