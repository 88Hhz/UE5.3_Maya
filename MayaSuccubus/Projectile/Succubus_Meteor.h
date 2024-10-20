// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Succubus_Projectile_Base.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Succubus_Meteor.generated.h"

/**
 * 
 */
UCLASS()
class MAYA53_API ASuccubus_Meteor : public ASuccubus_Projectile_Base
{
	GENERATED_BODY()
	
public:
	ASuccubus_Meteor();

	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	UNiagaraSystem* NSParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	UNiagaraComponent* NSComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	bool bIsThrow = false;

	UFUNCTION(BlueprintCallable, Category = "Function")
	void ThrowForward(float DeltaTime);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
