// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definitions.h"

#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;

USTRUCT(BlueprintType)
struct FInputObjetList
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inputs")
	class UInputAction* InputMove;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inputs")
	UInputAction* Looking;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inputs")
	UInputAction* Jump;
	
};

UCLASS()
class ABILITYSYSTEM_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	FInputObjetList InputList;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY()
	class APlayerControllerBase* PlayerCtr;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveCharacter(const FInputActionValue& Value);

	void LookCharacter(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
