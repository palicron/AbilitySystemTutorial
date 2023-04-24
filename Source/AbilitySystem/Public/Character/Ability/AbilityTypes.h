// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class UGameplayAbilityBase;

UENUM(BlueprintType)
enum class EAbilityCostType: uint8
{
	Health,
	Mana,
	Strength
	
};

USTRUCT(BlueprintType)

struct FGamePlayAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability Info")
	float CoolDownDuration;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability Info")
	float Cost;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability Info")
	EAbilityCostType CostType;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability Info")
	UMaterialInstance* UIMat;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability Info")
	TSubclassOf<UGameplayAbilityBase> Ability;

	FGamePlayAbilityInfo(): CoolDownDuration(0), Cost(0), CostType(), UIMat(nullptr),Ability(nullptr)
	{
	}
	;
	FGamePlayAbilityInfo(float InCd,float InCost,EAbilityCostType InCostType,UMaterialInstance* InUimat,TSubclassOf<UGameplayAbilityBase> INAbility):
	{
		CoolDownDuration = InCd;
		Cost = InCost;
		CostType = InCostType;
		UIMat = InUimat;
		Ability = INAbility;
	}
};