// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

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

void UAuraBeamSpell::StoreOwnerPlayerController()
{
	if(CurrentActorInfo)
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
	}
}
