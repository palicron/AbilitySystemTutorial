// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

void APlayerControllerBase::MoveCharacterForward(float Axis)
{
	const FRotator CamaraRotation =  PlayerCameraManager->GetCameraRotation();

	const FVector ForwardCamaraVector = UKismetMathLibrary::GetForwardVector(CamaraRotation);

	GetPawn()->AddMovementInput(ForwardCamaraVector,Axis);
	
}

void APlayerControllerBase::MoveCharacterRight(float AxisValue)
{
	const FRotator CamaraRotation =  PlayerCameraManager->GetCameraRotation();

	const FVector ForwardCamaraVector = UKismetMathLibrary::GetRightVector(CamaraRotation);

	GetPawn()->AddMovementInput(ForwardCamaraVector,AxisValue);
}

void APlayerControllerBase::CharacterJump()
{
	ACharacter* CharacterPawn = Cast<ACharacter>(GetPawn());
	if(CharacterPawn)
	{
		CharacterPawn->Jump();
	}
}
