// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffect.h"

UAttributeSetBase::UAttributeSetBase(): Health(200.f),Mana(100.f),Strength(100.f)
{
	MaxHealth = Health;
	MaxMana = Mana;
	MaxStrength = Strength;
}

void UAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if(Data.EvaluatedData.Attribute.GetUProperty() ==
		FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(),GET_MEMBER_NAME_CHECKED(UAttributeSetBase,Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(),0.f,MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(),0.f,MaxHealth.GetCurrentValue()));
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));	
		OnHealthChange.Broadcast(Health.GetCurrentValue(),MaxHealth.GetCurrentValue());
	}
	if(Data.EvaluatedData.Attribute.GetUProperty() ==
	FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(),GET_MEMBER_NAME_CHECKED(UAttributeSetBase,Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(),0.f,MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(),0.f,MaxMana.GetCurrentValue()));

		OnManaChange.Broadcast(Mana.GetCurrentValue(),MaxMana.GetCurrentValue());
	}
	if(Data.EvaluatedData.Attribute.GetUProperty() ==
	FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(),GET_MEMBER_NAME_CHECKED(UAttributeSetBase,Strength)))
	{
		Strength.SetCurrentValue(FMath::Clamp(Strength.GetCurrentValue(),0.f,MaxStrength.GetCurrentValue()));
		Strength.SetBaseValue(FMath::Clamp(Strength.GetBaseValue(),0.f,MaxStrength.GetCurrentValue()));

		OnStrChange.Broadcast(Strength.GetCurrentValue(),MaxStrength.GetCurrentValue());
	}
}
