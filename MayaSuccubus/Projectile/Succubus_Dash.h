// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Succubus_Projectile_Base.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Succubus_Dash.generated.h"

/**
 * 
 */
UCLASS()
class MAYA53_API ASuccubus_Dash : public ASuccubus_Projectile_Base
{
	GENERATED_BODY()
	
public:
	ASuccubus_Dash();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	UNiagaraSystem* NSParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	UNiagaraComponent* NSComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bool")
	bool bIsFollow = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FVector TargetLocation;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UFUNCTION()
	void MoveTowardTarget(float DeltaTime);

};
