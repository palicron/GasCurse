// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

#include "InputState.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraBeamSpell::StoreMouseDataInfo(const FHitResult& hitResult)
{
	if(hitResult.bBlockingHit)
	{
		MouseHitLocation = hitResult.ImpactPoint;
		MouseHitActor = hitResult.GetActor();
		return;
	}

	CancelAbility(CurrentSpecHandle,CurrentActorInfo, CurrentActivationInfo,true);
}

void UAuraBeamSpell::StoreOwnerVariables()
{
	if(CurrentActorInfo)
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
		OwnerPlayerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
	}
}

void UAuraBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	check(OwnerPlayerCharacter);
	if(!OwnerPlayerCharacter->Implements<UCombatInterface>())
	{
		return;
	}

	FVector SocketLocation = FVector::ZeroVector;
	if (USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerPlayerCharacter))
	{
		SocketLocation = Weapon->GetSocketLocation(FName("TipSocket"));
	}

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(OwnerPlayerCharacter);
	FHitResult HitResult;
	UKismetSystemLibrary::SphereTraceSingle(OwnerPlayerCharacter,
		SocketLocation,
		BeamTargetLocation,
		10.f,
		TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		false);

	if(HitResult.bBlockingHit)
	{
		MouseHitLocation = HitResult.ImpactPoint;
		MouseHitActor = HitResult.GetActor();
	}

	if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(MouseHitActor))
	{
		CombatInterface->GetOnDeathDelegate().AddUniqueDynamic(this,&UAuraBeamSpell::PrimaryTargetDied);
	}
}

void UAuraBeamSpell::StoreAdditionalTargets(TArray<AActor*>& OutAditinalTargets)
{
	TArray<AActor*> ActorToIgnore;
	ActorToIgnore.Add(GetAvatarActorFromActorInfo());
	ActorToIgnore.Add(MouseHitActor);
	TArray<AActor*> OverlappingActors;

	UAuraAbilitySystemLibrary::GetLifePlayerWithinRadius(GetAvatarActorFromActorInfo(), OverlappingActors,
	                                                     ActorToIgnore, 850.f,MouseHitActor->GetActorLocation());

	int32 NumAdditionalTargets = FMath::Min(GetAbilityLevel() - 1, MaxNumShockTargets);
	//int32 NumAdditionalTargets = 5;

	UAuraAbilitySystemLibrary::GetClosestTargets(NumAdditionalTargets, OverlappingActors, OutAditinalTargets,MouseHitActor->GetActorLocation());

	for (AActor* Target : OutAditinalTargets)
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Target))
		{
			CombatInterface->GetOnDeathDelegate().AddUniqueDynamic(this, &UAuraBeamSpell::AdditionalTargetDied);
		}
	}
}
