// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

#include "AbilitySystem/AuraAttributeSet.h"

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

float UAuraGameplayAbility::GetManaCost(float InLevel) const
{
	float ManaCost = 0.f;
	if(const UGameplayEffect* CostEffect = GetCostGameplayEffect())
	{
		for (FGameplayModifierInfo Mod : CostEffect->Modifiers)
		{
			if(Mod.Attribute == UAuraAttributeSet::GetManaAttribute())
			{
				Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel,ManaCost);
				break;
			}
		}
	}

	return ManaCost;
}
float UAuraGameplayAbility::GetCoolDown(float InLevel) const
{
	float CoolDown = 0.f;
	if(const UGameplayEffect* CoolDownEffect = GetCooldownGameplayEffect())
	{
		CoolDownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel,CoolDown);
	}

	return CoolDown;
}
