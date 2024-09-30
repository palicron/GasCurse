// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "AuraGamePlayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

FString UAuraFireBolt::GetDescription(const int32 Level) const
{
	const float  ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	if(Level == 1)
	{
		return FString::Printf(TEXT(
			"<TiTle>FIRE BOLT</>\n\n"
			"<Small>Level:</><Level>%d</>\n"
			"<Small>Mana Cost:</><ManaCost>%.1f</>\n"
			"<Small>Cooldown:</><Cooldown>%.1f</>\n\n"
			"<Default>Launches a bolt of fire, Exploding on impact and dealing: "
			 "</><Damage>%.1f</><Default> With a chance to burn.</>\n\n"),
			Level,FMath::Abs(ManaCost),Cooldown,ScaleDamage);
	}

	return FString::Printf(
		TEXT("<TiTle>FIRE BOLT</>\n\n"
		"<Small>Level:</><Level>%d:</>\n"
		"<Small>Mana Cost:</><ManaCost>%.1f</>\n"
		"<Small>Cooldown:</><Cooldown>%.1f</>\n\n"
		"<Default>Launches %d bolts of fire, Exploding on impact and dealing: </>"
			 "<Damage>%.1f</><Default> With a chance to burn. </>\n\n")
			 ,Level,FMath::Abs(ManaCost),Cooldown,FMath::Min(Level,NumberProjectiles),
			ScaleDamage);
}

FString UAuraFireBolt::GetNextLevelDescription(const int32 Level) const
{
	
	const float  ScaleDamage = Damage.GetValueAtLevel(Level);;
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(
		TEXT("<TiTle>FIRE BOLT</>\n\n"
		"<Small>Level:</><Level>%d:</>\n"
		"<Small>Mana Cost:</><ManaCost>%.1f</>\n"
		"<Small>Cooldown:</><Cooldown>%.1f</>\n\n"
		"<Default>Launches %d bolts of fire, Exploding on impact and dealing: </>"
			 "<Damage>%.1f</><Default> With a chance to burn. </>\n\n")
			 ,Level,FMath::Abs(ManaCost),Cooldown,FMath::Min(Level,NumberProjectiles),
			ScaleDamage);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,const bool bPitchOverRide, const float PitchOverRide, const AActor* HomingTarget)
{
	if (GetAvatarActorFromActorInfo()->HasAuthority())
	{
	
		const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

		if (bPitchOverRide)
		{
			Rotation.Pitch = PitchOverRide;
		}
	
		
		NumberProjectiles = FMath::Min(MaxNumProjectile, GetAbilityLevel());
		const FVector Forward = Rotation.Vector();

		TArray<FRotator> Direction = UAuraAbilitySystemLibrary::EvenlySpaceRotators(Forward, FVector::UpVector, ProjectileSpread, NumberProjectiles);

		for (const FRotator& Rotator : Direction)
		{
			FTransform SpawnTransform;

			SpawnTransform.SetLocation(SocketLocation);
			SpawnTransform.SetRotation(Rotator.Quaternion());


			AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
				ProjectileClass, SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(GetOwningActorFromActorInfo()),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

			if (HomingTarget && HomingTarget->Implements<UCombatInterface>())
			{
				Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
			}
			else
			{
				Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>( USceneComponent::StaticClass());
				Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
				Projectile->ProjectileMovement->HomingTargetComponent = Projectile->HomingTargetSceneComponent;
			}

			Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::RandRange(HomingAccelerationMin, HomingAccelerationMax);
			Projectile->ProjectileMovement->bIsHomingProjectile = bLaunchHomingProjectiles;
			Projectile->FinishSpawning(SpawnTransform);
		}
		
	}
}
