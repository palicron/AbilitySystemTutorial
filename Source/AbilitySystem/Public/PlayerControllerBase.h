// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:

	void MoveCharacterForward(float AxisValue);

	void MoveCharacterRight(float AxisValue);

	void CharacterJump();
	
};
