// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthPercetageChangeDelegate,float,CurrentHealth,float , MaxHealth);
UCLASS()
class ABILITYSYSTEM_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

private:

	UAttributeSetBase();

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute base")
		FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute base")
		FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute base")
	FGameplayAttributeData Mana;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute base")
	FGameplayAttributeData MaxMana;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute base")
	FGameplayAttributeData Strength;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute base")
	FGameplayAttributeData MaxStrength;

	UPROPERTY(BlueprintAssignable)
	FHealthPercetageChangeDelegate OnHealthChange;

	UPROPERTY(BlueprintAssignable)
	FHealthPercetageChangeDelegate OnManaChange;

	UPROPERTY(BlueprintAssignable)
	FHealthPercetageChangeDelegate OnStrChange;


	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
};
