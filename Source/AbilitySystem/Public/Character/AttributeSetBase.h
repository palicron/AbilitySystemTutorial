// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetBase.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

private:

	UAttributeSetBase();

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Attribute base")
		FGameplayAttributeData Health;
	
};
