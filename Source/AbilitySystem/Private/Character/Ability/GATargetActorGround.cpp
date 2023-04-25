// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Ability/GATargetActorGround.h"

#include <ocidl.h>

#include "Abilities/GameplayAbility.h"

void AGATargetActorGround::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	PrimaryPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AGATargetActorGround::ConfirmTargetingAndContinue()
{
	//Super::ConfirmTargetingAndContinue();

	if(PrimaryPC)
	{
		FVector ViewPoint;
		FRotator ViewRotation;

		PrimaryPC->GetPlayerViewPoint(ViewPoint,ViewRotation);

		FHitResult Resutl;

		FCollisionQueryParams QueryParams;
		
		QueryParams.bTraceComplex = false;

		APawn* MasterPawn = PrimaryPC->GetPawn();
		if(MasterPawn)
		{
			
		}
		FVector LookAtpoint;
		bool TryTrace = GetWorld()->LineTraceSingleByChannel(Resutl,ViewPoint,
			ViewPoint + ViewRotation.Vector()*10000.f,ECC_Visibility,QueryParams);
		if(TryTrace)
		{
			LookAtpoint = Resutl.ImpactPoint;
		}


		
	}

}
