// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definitions.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UGameplayAbility;
struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;
class UAbilitySystemComponent;

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

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inputs")
	UInputAction* MeleeAttack;
	
};

class UAttributeSetBase;

UCLASS()
class ABILITYSYSTEM_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
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

	UFUNCTION()
	void MoveCharacter(const FInputActionValue& Value);

	UFUNCTION()
	void LookCharacter(const FInputActionValue& Value);

	UFUNCTION()
	void JumpCharacter(const FInputActionValue& Value);

	UFUNCTION()
	void MeleeAttack(const FInputActionValue& Value);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Character Base")
	UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Character Base")
	UAttributeSetBase* AttributeSerBaseComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Game Ability")
	TSubclassOf<UGameplayAbility> AbilityAttackRef;

	UFUNCTION(BlueprintCallable,Category="Character Base")
	void AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire);
	


};
