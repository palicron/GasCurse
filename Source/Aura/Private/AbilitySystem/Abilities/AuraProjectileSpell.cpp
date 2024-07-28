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



FString UAuraProjectileSpell::GetDescription(const int32 Level) const
{
	const int32 ScaleDamage = DamageTypes[FAuraGamePlayTags::Get().Damage_Fire].GetValueAtLevel(GetAbilityLevel());
	if(Level == 1)
	{
		return FString::Printf(TEXT("<TiTle>FIRE BOLT</>\n\n<Default>Launches a bolt of fire, Exploding on impact and dealing: </><Damage>%d</><Default> With a chance to burn: </>\n\n<Small>Level:</><Level>%d</>"),ScaleDamage,Level);
	}

	return FString::Printf(TEXT("<TiTle>FIRE BOLT</>\n\n<Default>Launches %d bolts of fire, Exploding on impact and dealing: </><Damage>%d</> <Default> With a chance to burn: </>\n\n<Small>Level:</><Level>%d:</>"),FMath::Min(Level,NumberProjectiles),ScaleDamage,Level);
}

FString UAuraProjectileSpell::GetNextLevelDescription(const int32 Level) const
{
	const int32 ScaleDamage = DamageTypes[FAuraGamePlayTags::Get().Damage_Fire].GetValueAtLevel(Level);
	
	return FString::Printf(TEXT("<TiTle>NEXT LEVEL</>\n\n<Default>Launches %d bolts of fire, Exploding on impact and dealing: </><Damage>%d</> <Default> With a chance to burn: </>\n\n<Small>Level:</><Level>%d:</>"),FMath::Min(Level,NumberProjectiles),ScaleDamage,Level);	
}
