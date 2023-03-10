// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Public/Character/CharacterBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "PlayerControllerBase.h"
#include "AbilitySystemComponent.h"
#include "Character/AttributeSetBase.h"

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

	AcquireAbility(AbilityAttackRef);
	
	
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


UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

