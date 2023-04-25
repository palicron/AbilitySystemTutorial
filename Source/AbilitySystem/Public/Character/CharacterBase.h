// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definitions.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UGameplayAbilityBase;
struct FGameplayTag;
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

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inputs")
	UInputAction* HealthRegent;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inputs")
	UInputAction* DashInput;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inputs")
	UInputAction* AbilitySlot3;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inputs")
	UInputAction* AbilitySlot4;
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
	
	UFUNCTION()
	void RegentHealth();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_RegentHealth();

	UFUNCTION()
	void DashAction();

	UFUNCTION()
	void SlotAbility3();

	UFUNCTION()
	void SlotAbility4();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_DashAction();
	
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

	UFUNCTION(BlueprintCallable)
	void MeleeAttack(const FInputActionValue& Value);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsDeath = false;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	uint8 TeamID = 255;

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

	UFUNCTION(BlueprintCallable,Category="Character Base")
	void AcquireAbilitys(TArray<TSubclassOf<UGameplayAbility>> AbilitysToAcquire);


	UFUNCTION()
	void OnHealthChanged(float CurrentHealth,float MaxHealth);
	
	UFUNCTION()
	void OnManaChange(float CurrentMana,float MaxMana);
	
	UFUNCTION()
	void OnStrChange(float CurrenStr,float MaxStr);

	UFUNCTION(BlueprintCallable)
	void HitStun(float StunDuration);

	FTimerHandle StunTimeHandler;
	
	UFUNCTION(BlueprintCallable)
	void EnableInputs() const;
	
	UFUNCTION(BlueprintCallable)
	void DisableInputs() const;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase" , meta=(DisplayName="OnHealthChange" ))
	void BP_OnHealthChange(float CurrentHealth,float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase" , meta=(DisplayName="nManaChange" ))
	void BP_OnManaChange(float CurrentMana,float MaxMana);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase" , meta=(DisplayName="OnStrChange" ))
	void BP_OnStrChange(float CurrenStr,float MaxStr);
	
	UFUNCTION(BlueprintCallable,Category="Character Base")
	bool IsOtherHostile(ACharacterBase* other);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase" , meta=(DisplayName="Die" ))
	void BP_Die();


	UFUNCTION(BlueprintCallable,Category="Character Base")
	void AddGamePlayTag(FGameplayTag& TagToAdd);

	UFUNCTION(BlueprintCallable,Category="Character Base")
	void RemoveGamePlayTag(FGameplayTag& TagToRemove);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGameplayTag FUllHealthTag;
	
	UFUNCTION()
	void DeterminTeamIdByVontrollerType();

protected:

	void AddAbilityToUI(TSubclassOf<UGameplayAbilityBase> Ability);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnSlotButtonPress(int32 Slot);

};
