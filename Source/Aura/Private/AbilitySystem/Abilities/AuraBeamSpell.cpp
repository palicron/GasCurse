// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

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
	if(OwnerPlayerCharacter->Implements<UCombatInterface>())
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
		EDrawDebugTrace::ForDuration,
		HitResult,
		false);

	if(HitResult.bBlockingHit)
	{
		MouseHitLocation = HitResult.ImpactPoint;
		MouseHitActor = HitResult.GetActor();
	}
}
