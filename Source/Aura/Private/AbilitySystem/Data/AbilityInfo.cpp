// CAS Tutorial JsPalacios


#include "AbilitySystem/Data/AbilityInfo.h"

#include "Aura/AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag AbilityTag, bool bLogNotFound) const
{
	if(AbilityInformation.Contains(AbilityTag))
	{
		return AbilityInformation[AbilityTag];
	}

	if(bLogNotFound)
	{
		UE_LOG(LogAura,Error,TEXT("Cant find info for AbilityTag %s on AbilityInfo %s"),*AbilityTag.ToString(),*GetNameSafe(this));
	}

	return FAuraAbilityInfo();
}
