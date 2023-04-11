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

	UPROPERTY(BlueprintAssignable)
	FHealthPercetageChangeDelegate OnHealthChange;


	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
};
