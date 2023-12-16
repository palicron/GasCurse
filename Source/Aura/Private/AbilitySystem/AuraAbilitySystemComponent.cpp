// CAS Tutorial JsPalacios


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGamePlayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
	
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComp,
                                                const FGameplayEffectSpec& GamePlaySpec, FActiveGameplayEffectHandle ActiveHandel)
{
	FGameplayTagContainer TagContainer;
	GamePlaySpec.GetAllAssetTags(TagContainer);
	EffectAssetTagsDelegate.Broadcast(TagContainer);
}
