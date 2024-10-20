// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorInteractionManager.h"




void UActorInteractionManager::SetAkkatActor(AActor* Actor)
{
	Akkat = Actor;
}

void UActorInteractionManager::SetDoorActor(AActor* Actor)
{
	Door = Actor;
}

void UActorInteractionManager::SetBossActor(AActor* Actor)
{
	Boss = Actor;
}