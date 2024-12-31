// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/ArcaneShards.h"

FString UArcaneShards::GetDescription(const int32 Level) const
{
	const float  ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	if(Level == 1)
	{
		return FString::Printf(TEXT(
			"<TiTle>ARCANE SHARDS</>\n\n"
			"<Small>Level:</><Level>%d</>\n"
			"<Small>Mana Cost:</><ManaCost>%.1f</>\n"
			"<Small>Cooldown:</><Cooldown>%.1f</>\n\n"
			"<Default>Summon Shards of Arcane energy, causing radial damage of : "
			 "</><Damage>%.1f</><Default> At the shard origen.</>\n\n"),
			Level,FMath::Abs(ManaCost),Cooldown,ScaleDamage);
	}

	return FString::Printf(
		TEXT("<TiTle>ARCANE SHARDS</>\n\n"
		"<Small>Level:</><Level>%d:</>\n"
		"<Small>Mana Cost:</><ManaCost>%.1f</>\n"
		"<Small>Cooldown:</><Cooldown>%.1f</>\n\n"
		"<Default> Summon %d shards of arcane energy, causing Radial Arcane Damage of  : </>"
			 "<Damage>%.1f</><Default> At the shard origen. </>\n\n")
			 ,Level,FMath::Abs(ManaCost),
			 Cooldown,
			 FMath::Min(Level,MaxNumbShards),
			ScaleDamage);
}

FString UArcaneShards::GetNextLevelDescription(const int32 Level) const
{
	const float  ScaleDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);

	return FString::Printf(
	TEXT("<TiTle>ARCANE SHARDS</>\n\n"
	"<Small>Level:</><Level>%d:</>\n"
	"<Small>Mana Cost:</><ManaCost>%.1f</>\n"
	"<Small>Cooldown:</><Cooldown>%.1f</>\n\n"
	"<Default> Summon %d shards of arcane energy, causing Radial Arcane Damage of  : </>"
		 "<Damage>%.1f</><Default> At the shard origen. </>\n\n")
		 ,Level,FMath::Abs(ManaCost),
		 Cooldown,
		 FMath::Min(Level,MaxNumbShards ),
		ScaleDamage);
}
