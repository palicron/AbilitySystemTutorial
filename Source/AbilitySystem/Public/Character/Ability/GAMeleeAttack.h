// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GAMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API UGAMeleeAttack : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void K2_EndAbility() override;
	
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	UAnimMontage* MeleeAttackMontage;

	void PlayMontage();
	
};
