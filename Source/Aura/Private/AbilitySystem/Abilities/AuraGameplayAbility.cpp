// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

FString UAuraGameplayAbility::GetDescription(const int32 Level) const
{
	return FString::Printf(TEXT("<Default>%s, Ability Level =  </><Level> %d, </>"),L"Default Ability Name - LoremIpsum LoremIpsum  LoremIpsum  LoremIpsum  LoremIpsum  LoremIpsum  LoremIpsum  LoremIpsum  LoremIpsum",Level);
}

FString UAuraGameplayAbility::GetNextLevelDescription(const int32 Level) const
{
	return FString::Printf(TEXT("<Default>%s, Ability Level = </><Level>%d, </>"),L"Default Ability Name - LoremIpsum LoremIpsum  LoremIpsum  LoremIpsum  LoremIpsum  LoremIpsum  LoremIpsum  LoremIpsum  LoremIpsum",Level + 1);
}

FString UAuraGameplayAbility::GetLockDescription(const int32 Level)
{
	return FString::Printf(TEXT("<Default>Spell Locked Until Level : </><Level>%d, </>"), Level);
}
