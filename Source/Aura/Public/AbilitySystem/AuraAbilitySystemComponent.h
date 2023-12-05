// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	void AbilityActorInfoSet();
	
protected:

	void EffectApplied(UAbilitySystemComponent* AbilitySystemComp, const FGameplayEffectSpec& GamePlaySpec, FActiveGameplayEffectHandle ActiveHandel);
	
};
