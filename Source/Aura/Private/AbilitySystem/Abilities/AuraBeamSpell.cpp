// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

#include "GameFramework/Character.h"

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
