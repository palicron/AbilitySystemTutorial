// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffect.h"

UAttributeSetBase::UAttributeSetBase(): Health(200.f)
{
	MaxHealth = Health;
}

void UAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if(Data.EvaluatedData.Attribute.GetUProperty() ==
		FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(),GET_MEMBER_NAME_CHECKED(UAttributeSetBase,Health)))
	{
		UE_LOG(LogTemp,Warning,TEXT("DAmage take healt %f"),Health.GetCurrentValue());
		OnHealthChange.Broadcast(Health.GetCurrentValue(),MaxHealth.GetCurrentValue());
	}
}
