// CAS Tutorial JsPalacios


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound)
{
	if(AttributeInformation.Contains(AttributeTag))
	{
		return AttributeInformation[AttributeTag];
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Cant find info for AttributeTag %s on AttributeInfo %s"),*AttributeTag.ToString(),*GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}
