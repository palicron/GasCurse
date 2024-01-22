// CAS Tutorial JsPalacios


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const FAuraInputAction& Action : AbilityInputActions)
	{
		if(Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Cant find abilityInputAction for input Tag %s on InputConfig %s"),*InputTag.ToString(),*GetNameSafe(this));
	}

	return nullptr;
}
