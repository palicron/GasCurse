// CAS Tutorial JsPalacios


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComp,
                                                const FGameplayEffectSpec& GamePlaySpec, FActiveGameplayEffectHandle ActiveHandel)
{
	FGameplayTagContainer TagContainer;
	GamePlaySpec.GetAllAssetTags(TagContainer);
	for (const FGameplayTag& Element : TagContainer)
	{
		//TODO Brodcast the tag to th widget controller
	}
}
