// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
UCLASS()
class ABILITYSYSTEM_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	UCameraComponent* CameraComponent;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
