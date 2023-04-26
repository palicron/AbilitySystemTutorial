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

public:

	AGATargetActorGround();

	virtual void Tick(float DeltaSeconds) override;
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	UFUNCTION(BlueprintCallable)
	bool GetPlayerLocationPoint(FVector& OutViewPoint);

	virtual void ConfirmTargetingAndContinue() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(ExposeOnSpawn=true))
	float Radius = 250.f;
	
};
