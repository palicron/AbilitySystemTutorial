// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Ability/GameplayAbilityBase.h"

#include "Character/Ability/AbilityTypes.h"

FGamePlayAbilityInfo UGameplayAbilityBase::GetAbilityInfo()
{
	UGameplayEffect* CoolDownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();
	if(CoolDownEffect && CostEffect )
	{
		
		float CoolDownDuration = 0;
		CoolDownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1,CoolDownDuration);
		float CostDownDuration = 0;
		EAbilityCostType CostType = EAbilityCostType::Health;
		if(CostEffect->Modifiers.Num()>0)
		{
			FGameplayModifierInfo ModifyInfo = CostEffect->Modifiers[0];
			ModifyInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1,CostDownDuration);
			FGameplayAttribute CostAttr = ModifyInfo.Attribute;
			FString AttributeName = CostAttr.AttributeName;
			if(AttributeName == "Health")
			{
				CostType = EAbilityCostType::Health;
			}
			else if(AttributeName == "Mana")
			{
				CostType = EAbilityCostType::Mana;
			}
			else
			{
				CostType = EAbilityCostType::Strength;
			}
		}
		return FGamePlayAbilityInfo(CoolDownDuration,CostDownDuration,CostType,UIMaterial,GetClass());
	}
	return FGamePlayAbilityInfo();
}
