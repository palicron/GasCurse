// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if(HasAuthority(&ActivationInfo))
	{
		if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
		{
			const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
			FTransform SpawnTransform;
			//Todo: Set De Projectile location
			SpawnTransform.SetLocation(SocketLocation);
			AAuraProjectile* Projectile =  GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform,
															GetOwningActorFromActorInfo(),
															Cast<APawn>(GetOwningActorFromActorInfo()),
															ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			//TODO: Give the Projectile A Gameplay effect for causing Damage 

			Projectile->FinishSpawning(SpawnTransform);
		}
		
	}
}
