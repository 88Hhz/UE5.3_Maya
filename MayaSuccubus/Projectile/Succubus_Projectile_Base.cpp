// Fill out your copyright notice in the Description page of Project Settings.


#include "Succubus_Projectile_Base.h"

//Particle System
#include "kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"


// Sets default values
ASuccubus_Projectile_Base::ASuccubus_Projectile_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	FVector BoxSize = FVector(32.f, 32.f, 32.f);
	BoxCollision->SetBoxExtent(BoxSize);
	BoxCollision->SetupAttachment(StaticMesh);


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->SetUpdatedComponent(BoxCollision);
	ProjectileMovement->InitialSpeed = InitialSpeed;
	ProjectileMovement->MaxSpeed = InitialSpeed;
	ProjectileMovement->ProjectileGravityScale = GravityScale;
	ProjectileMovement->bRotationFollowsVelocity = true;

	BoxCollision->OnComponentHit.AddDynamic(this, &ASuccubus_Projectile_Base::OnHit);
}

// Called when the game starts or when spawned
void ASuccubus_Projectile_Base::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASuccubus_Projectile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ASuccubus_Projectile_Base::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{


}

void ASuccubus_Projectile_Base::DestroyProjectile()
{
	GetWorld()->DestroyActor(this);
}