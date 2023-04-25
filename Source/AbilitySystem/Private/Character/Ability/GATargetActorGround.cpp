// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Ability/GATargetActorGround.h"

#include <ocidl.h>

#include "Abilities/GameplayAbility.h"

void AGATargetActorGround::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	PrimaryPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

bool  AGATargetActorGround::GetPlayerLocationPoint(FVector& OutViewPoint)
{
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
			QueryParams.AddIgnoredActor(MasterPawn);
		}
	
		bool TryTrace = GetWorld()->LineTraceSingleByChannel(Resutl,ViewPoint,
		                                                     ViewPoint + ViewRotation.Vector()*10000.f,ECC_Visibility,QueryParams);
		if(TryTrace)
		{
			OutViewPoint = Resutl.ImpactPoint;
			return true;
		}
	
		
	}
	return false;
}

void AGATargetActorGround::ConfirmTargetingAndContinue()
{
	//Super::ConfirmTargetingAndContinue();

	FVector ViewLocation;
	GetPlayerLocationPoint(ViewLocation);

	TArray<FOverlapResult> OverlapsActor;
	TArray<TWeakObjectPtr<AActor>> OverLapedActors;

	FCollisionQueryParams Parms;
	Parms.bTraceComplex = false;
	Parms.bReturnPhysicalMaterial = false;
	APawn* MasterPawn = PrimaryPC->GetPawn();
	if(MasterPawn)
	{
		Parms.AddIgnoredActor(MasterPawn);
	}

	bool tryOverlap = GetWorld()->OverlapMultiByObjectType(OverlapsActor,ViewLocation,FQuat::Identity,FCollisionObjectQueryParams(ECC_Pawn)
		,FCollisionShape::MakeSphere(Radius),Parms);
	
	if(tryOverlap)
	{
		for (const FOverlapResult& Hit : OverlapsActor)
		{
			APawn* OverlapPawn = Cast<APawn>(Hit.GetActor());
			if(OverlapPawn && !OverLapedActors.Contains(OverlapPawn))
			{
				OverLapedActors.Add(OverlapPawn);
			}
		}
	}
	
}
