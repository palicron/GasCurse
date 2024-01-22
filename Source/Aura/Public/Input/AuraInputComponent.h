// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserClass,typename PressedFuncType,typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputsConfig,UserClass* Object,PressedFuncType PressedFunc,ReleasedFuncType ReleasedFunc,HeldFuncType HeldFunc);
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputsConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputsConfig);

	for (const FAuraInputAction& Actions : InputsConfig->AbilityInputActions)
	{
		if(Actions.InputAction && Actions.InputTag.IsValid())
		{

			if(PressedFunc)
			{
				BindAction(Actions.InputAction,ETriggerEvent::Started,Object,PressedFunc,Actions.InputTag);
			}

			if(ReleasedFunc)
			{
				BindAction(Actions.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,Actions.InputTag);
			}
			
			if(HeldFunc)
			{
				BindAction(Actions.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,Actions.InputTag);
			}
			
		}
	}
}
