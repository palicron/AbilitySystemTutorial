// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorGround.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API AGATargetActorGround : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;
	
};
