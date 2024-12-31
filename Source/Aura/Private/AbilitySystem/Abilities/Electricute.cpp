// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/Electricute.h"

FString UElectricute::GetDescription(const int32 Level) const
{
	const float  ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	if(Level == 1)
	{
		return FString::Printf(TEXT(
			"<TiTle>ELECTROCUTE</>\n\n"
			"<Small>Level:</><Level>%d</>\n"
			"<Small>Mana Cost:</><ManaCost>%.1f</>\n"
			"<Small>Cooldown:</><Cooldown>%.1f</>\n\n"
			"<Default>Emits a beam og lighting, Connecting whit the target, repeatedly causing : "
			 "</><Damage>%.1f</><Default> With a chance to Stun.</>\n\n"),
			Level,FMath::Abs(ManaCost),Cooldown,ScaleDamage);
	}

	return FString::Printf(
		TEXT("<TiTle>ELECTROCUTE</>\n\n"
		"<Small>Level:</><Level>%d:</>\n"
		"<Small>Mana Cost:</><ManaCost>%.1f</>\n"
		"<Small>Cooldown:</><Cooldown>%.1f</>\n\n"
		"<Default> Emits a beam of lightning, propagating to %d Additional Targets : </>"
			 "<Damage>%.1f</><Default> With a chance to Stun. </>\n\n")
			 ,Level,FMath::Abs(ManaCost),
			 Cooldown,
			 FMath::Min(Level,MaxNumShockTargets - 1),
			ScaleDamage);
}

FString UElectricute::GetNextLevelDescription(const int32 Level) const
{
	const float  ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	
	return FString::Printf(
	TEXT("<TiTle>NEXT LEVEL</>\n\n"
	"<Small>Level:</><Level>%d:</>\n"
	"<Small>Mana Cost:</><ManaCost>%.1f</>\n"
	"<Small>Cooldown:</><Cooldown>%.1f</>\n\n"
	"<Default> Emits a beam of lightning, propagating to %d Additional Targets : </>"
		 "<Damage>%.1f</><Default> With a chance to Stun. </>\n\n")
		 ,Level,FMath::Abs(ManaCost),
		 Cooldown,
		 FMath::Min(Level,MaxNumShockTargets - 1),
		ScaleDamage);
}
