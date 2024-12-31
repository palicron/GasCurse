// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraFireBlast.h"

FString UAuraFireBlast::GetDescription(const int32 Level) const
{
	const float  ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	
		return FString::Printf(TEXT(
			"<TiTle>FIRE BLAST</>\n\n"
			"<Small>Level:</><Level>%d</>\n"
			"<Small>Mana Cost:</><ManaCost>%.1f</>\n"
			"<Small>Cooldown:</><Cooldown>%.1f</>\n\n"
			"<Default>Launches %d: </> "
			"Fire balls in all Direction, each coming back and </>"
			"Exploding upon return casing </>"
			 "</><Damage>%.1f</><Default> Radial fire damage,With a chance to burn.</>\n\n"),
			Level,FMath::Abs(ManaCost),
			Cooldown,
			NumFireBalls,
			ScaleDamage);
}

FString UAuraFireBlast::GetNextLevelDescription(const int32 Level) const
{
	const float  ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	
	return FString::Printf(TEXT(
		"<TiTle>NEXT LEVEL</>\n\n"
		"<Small>Level:</><Level>%d</>\n"
		"<Small>Mana Cost:</><ManaCost>%.1f</>\n"
		"<Small>Cooldown:</><Cooldown>%.1f</>\n\n"
		"<Default>Launches %d: </> "
		"Fire balls in all Direction, each coming back and </>"
		"Exploding upon return casing </>"
		 "</><Damage>%.1f</><Default> Radial fire damage,With a chance to burn.</>\n\n"),
		Level,FMath::Abs(ManaCost),
		Cooldown,
		NumFireBalls,
		ScaleDamage);
}
