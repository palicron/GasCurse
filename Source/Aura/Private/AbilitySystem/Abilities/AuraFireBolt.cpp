// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "AuraGamePlayTags.h"
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

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, const AActor* HomingTarget)
{
	if (GetAvatarActorFromActorInfo()->HasAuthority())
	{
		FTransform SpawnTransform;
		const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(),SocketTag);
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;
		
		SpawnTransform.SetRotation(Rotation.Quaternion());
		SpawnTransform.SetLocation(SocketLocation);

		NumberProjectiles = FMath::Min(MaxNumProjectile,GetAbilityLevel());
		const FVector Forward = Rotation.Vector();
		const FVector LeftSpread = Forward.RotateAngleAxis(-ProjectileSpread/2.f,FVector::UpVector);
		
		if(NumberProjectiles > 1)
		{
			const float DeltaSpread = ProjectileSpread / (NumberProjectiles - 1);
			for (int32 i = 0; i < NumberProjectiles; i++)
			{
				const FVector Direction = LeftSpread.RotateAngleAxis(DeltaSpread * i ,FVector::UpVector);
			}
		}
		else
		{
			//single projectiles
		}
			
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),SocketLocation,SocketLocation + Rotation.Vector() * 200.f,5,FLinearColor::White,60.f,2);
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(),SocketLocation,SocketLocation + LeftSpread * 200.f,5,FLinearColor::Green,60.f,2);
	}
}
