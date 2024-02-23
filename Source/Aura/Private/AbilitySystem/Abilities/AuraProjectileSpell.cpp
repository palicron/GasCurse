// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation) 
{
	if (GetAvatarActorFromActorInfo()->HasAuthority())
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
		{
			const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
			FTransform SpawnTransform;

			SpawnTransform.SetLocation(SocketLocation);

			FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
			Rotation.Pitch = 0.f;

			SpawnTransform.SetRotation(Rotation.Quaternion());

			AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
				ProjectileClass, SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(GetOwningActorFromActorInfo()),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			const UAbilitySystemComponent* SourceASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

			const FGameplayEffectSpecHandle SpecHandel = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(),SourceASC->MakeEffectContext() );
			FAuraGamePlayTags GamePlayTags = FAuraGamePlayTags::Get();
		
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandel,GamePlayTags.Damage,Damage.GetValueAtLevel(GetAbilityLevel()));
			Projectile->DamageEffectHandle = SpecHandel;
			
			Projectile->FinishSpawning(SpawnTransform);
		}
	}
}
