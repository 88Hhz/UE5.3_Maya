// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Succubus_Projectile_Base.generated.h"

UCLASS()
class MAYA53_API ASuccubus_Projectile_Base : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASuccubus_Projectile_Base();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	float InitialSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	float GravityScale = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
	UParticleSystem* ImpactEffect;

	UFUNCTION(BlueprintCallable, Category = "Function")
	virtual void DestroyProjectile();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnyWhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;


	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
