// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Public/Character/CharacterBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "PlayerControllerBase.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "Character/AttributeSetBase.h"
#include "Character/Ability/AbilityTypes.h"
#include "Character/Ability/GameplayAbilityBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerEye"));

	AttributeSerBaseComp = CreateDefaultSubobject<UAttributeSetBase>(TEXT("Attribute Set Base"));

	CameraComponent->SetupAttachment(SpringArmComponent);

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
}



// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCtr = Cast<APlayerControllerBase>(Controller);

	//AcquireAbility(AbilityAttackRef);
	
	AttributeSerBaseComp->OnHealthChange.AddDynamic(this,&ThisClass::ACharacterBase::OnHealthChanged);
	AttributeSerBaseComp->OnManaChange.AddDynamic(this,&ThisClass::ACharacterBase::OnManaChange);
	AttributeSerBaseComp->OnStrChange.AddDynamic(this,&ThisClass::ACharacterBase::OnStrChange);
	
	DeterminTeamIdByVontrollerType();

	AddGamePlayTag(FUllHealthTag);
	
}



// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PC = Cast<APlayerController>(GetController());
 
	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if(IsValid(Subsystem))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMapping, 0);
	}

	if(IsValid(PEI) )
	{
		if(InputList.InputMove)
		{
			PEI->BindAction(InputList.InputMove,ETriggerEvent::Triggered,this,&ThisClass::MoveCharacter);
		}

		if(InputList.Looking)
		{
			PEI->BindAction(InputList.Looking,ETriggerEvent::Triggered,this,&ThisClass::LookCharacter);
		}

		if(InputList.Jump)
		{
			PEI->BindAction(InputList.Jump,ETriggerEvent::Triggered,this,&ThisClass::JumpCharacter);
		}

		if(InputList.MeleeAttack)
		{
			PEI->BindAction(InputList.MeleeAttack,ETriggerEvent::Started,this,&ThisClass::MeleeAttack);
		}
		if(InputList.HealthRegent)
		{
			PEI->BindAction(InputList.HealthRegent,ETriggerEvent::Started,this,&ACharacterBase::RegentHealth);
		}
		if(InputList.DashInput)
		{
			PEI->BindAction(InputList.DashInput,ETriggerEvent::Started,this,&ACharacterBase::DashAction);
		}
		
	}
}


void ACharacterBase::MoveCharacter(const FInputActionValue& Value)
{
	if(IsValid(PlayerCtr))
	{
		const FVector2d MoveValue = Value.Get<FVector2d>();
		if(MoveValue.Y != 0.f)
		{
			PlayerCtr->MoveCharacterForward(MoveValue.Y);
		}

		if(MoveValue.X != 0.f)
		{
			PlayerCtr->MoveCharacterRight(MoveValue.X);
		}
	}
}

void ACharacterBase::LookCharacter(const FInputActionValue& Value)
{
	if(IsValid(PlayerCtr))
	{
		const FVector2d LookValue = Value.Get<FVector2d>();

		if(LookValue.X != 0.f)
		{
			AddControllerYawInput(LookValue.X);
		}

		if(LookValue.Y != 0.f)
		{
			AddControllerPitchInput(LookValue.Y);
		}
		
	}
}

void ACharacterBase::JumpCharacter(const FInputActionValue& Value)
{
	if(IsValid(PlayerCtr))
	{
		PlayerCtr->CharacterJump();
	}
}

void ACharacterBase::MeleeAttack(const FInputActionValue& Value)
{
	if(IsValid(AbilitySystemComp))
	{
		AbilitySystemComp->TryActivateAbilityByClass(AbilityAttackRef);
	}
	return;

}

void ACharacterBase::AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire)
{
	if(IsValid(AbilitySystemComp))
	{
		if(HasAuthority() && AbilityToAcquire)
		{
			FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
			SpecDef.Ability = AbilityToAcquire;
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(SpecDef,1);
			AbilitySystemComp->GiveAbility(AbilitySpec);
		}
		
		AbilitySystemComp->InitAbilityActorInfo(this,this);
	}
}

void ACharacterBase::AcquireAbilitys(TArray<TSubclassOf<UGameplayAbility>> AbilitysToAcquire)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : AbilitysToAcquire)
	{
		AcquireAbility(Ability);
		if(Ability->IsChildOf(UGameplayAbilityBase::StaticClass()))
		{
			TSubclassOf<UGameplayAbilityBase> AbilityBaseClass = * Ability;
			if(Ability!=nullptr)
			{
			AddAbilityToUI(AbilityBaseClass);
			}
		}
	}
}

void ACharacterBase::OnHealthChanged(float CurrentHealth, float MaxHealth)
{
	BP_OnHealthChange(CurrentHealth,MaxHealth);
	if(CurrentHealth <= 0.f && !bIsDeath)
	{
		bIsDeath = true;
		
		DisableInputs();
		
		BP_Die();
	}
}

void ACharacterBase::OnManaChange(float CurrentMana, float MaxMana)
{
	BP_OnManaChange(CurrentMana,MaxMana);
}

void ACharacterBase::OnStrChange(float CurrenStr, float MaxStr)
{
	BP_OnStrChange(CurrenStr,MaxStr);
}

void ACharacterBase::HitStun(float StunDuration)
{
	DisableInputs();

	GetWorld()->GetTimerManager().SetTimer(StunTimeHandler,this,&ACharacterBase::EnableInputs,StunDuration,false);
}

void ACharacterBase::EnableInputs() const
{
	if(bIsDeath)
		return;
	if(IsValid(PlayerCtr))
	{
		PlayerCtr->EnableInput(PlayerCtr);
	
	}
	AAIController* AIC = Cast<AAIController>(GetController());
	if(IsValid(AIC))
	{
		AIC->GetBrainComponent()->StartLogic();
	}
}

void ACharacterBase::DisableInputs() const
{

	if(IsValid(PlayerCtr))
	{
		PlayerCtr->DisableInput(PlayerCtr);

	}
	AAIController* AIC = Cast<AAIController>(GetController());
	if(IsValid(AIC))
	{
		AIC->GetBrainComponent()->StopLogic("Dead");
	}

}

bool ACharacterBase::IsOtherHostile(ACharacterBase* other)
{
	
	return (IsValid(other) && other->TeamID!=TeamID);
}

void ACharacterBase::AddGamePlayTag(FGameplayTag& TagToAdd)
{
	GetAbilitySystemComponent()->AddLooseGameplayTag(TagToAdd);
	GetAbilitySystemComponent()->SetTagMapCount(TagToAdd,1);
}

void ACharacterBase::RemoveGamePlayTag(FGameplayTag& TagToRemove)
{
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(TagToRemove);
}

void ACharacterBase::DeterminTeamIdByVontrollerType()
{
	if(GetController() && GetController()->IsPlayerController())
	{
		TeamID = 0;
	}
	else
	{
		TeamID = 1;
	}
}

void ACharacterBase::AddAbilityToUI(TSubclassOf<UGameplayAbilityBase> Ability)
{
	APlayerControllerBase* PlayerControlerBase = Cast<APlayerControllerBase>(GetController());
	if(PlayerControlerBase)
	{
		UGameplayAbilityBase* AbilityInstace = Ability.Get()->GetDefaultObject<UGameplayAbilityBase>();
		if(AbilityInstace)
		{
			FGamePlayAbilityInfo AbilityInfo = AbilityInstace->GetAbilityInfo();
			PlayerControlerBase->AddAbilityToUI(AbilityInfo);
		}
	}
}


UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}
void ACharacterBase::RegentHealth()
{
	BP_OnSlotButtonPress(0);
	//BP_RegentHealth();
}

void ACharacterBase::DashAction()
{
	BP_OnSlotButtonPress(1);
	//BP_DashAction();
}




