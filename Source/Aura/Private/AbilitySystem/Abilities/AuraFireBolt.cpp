// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "AuraGamePlayTags.h"

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