// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "AuraGamePlayTags.h"
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

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag) 
{
	if (GetAvatarActorFromActorInfo()->HasAuthority())
	{
		const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(),SocketTag);
		FTransform SpawnTransform;

		SpawnTransform.SetLocation(SocketLocation);

		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();


		SpawnTransform.SetRotation(Rotation.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass, SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
			GetAvatarActorFromActorInfo());

		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(Projectile);
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(Projectile);
		EffectContextHandle.AddActors(Actors);
		FHitResult HitResult;
		HitResult.Location = ProjectileTargetLocation;
		EffectContextHandle.AddHitResult(HitResult);

		const FGameplayEffectSpecHandle SpecHandel = SourceASC->MakeOutgoingSpec(
			DamageEffectClass, GetAbilityLevel(), EffectContextHandle);


		for (auto& Pair : DamageTypes)
		{
			const float ScaleDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandel, Pair.Key, ScaleDamage);
		}
		FAuraGamePlayTags GamePlayTags = FAuraGamePlayTags::Get();

		Projectile->DamageEffectHandle = SpecHandel;

		Projectile->FinishSpawning(SpawnTransform);
		
	}
}




