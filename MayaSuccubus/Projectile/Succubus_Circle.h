// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Succubus_Projectile_Base.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Succubus_Circle.generated.h"

/**
 * 
 */
UCLASS()
class MAYA53_API ASuccubus_Circle : public ASuccubus_Projectile_Base
{
	GENERATED_BODY()
	
public:
	ASuccubus_Circle();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	UNiagaraSystem* NSParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	UNiagaraComponent* NSComponent;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
