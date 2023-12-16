// CAS Tutorial JsPalacios


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGamePlayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);

	const FAuraGamePlayTags& GamePlayTags = FAuraGamePlayTags::Get();

	//GamePlayTags.Attributes_Secondary_Armor.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, FString::Printf(TEXT("Tag: %s"),
	                                 *GamePlayTags.Attributes_Secondary_Armor.ToString()));
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComp,
                                                const FGameplayEffectSpec& GamePlaySpec, FActiveGameplayEffectHandle ActiveHandel)
{
	FGameplayTagContainer TagContainer;
	GamePlaySpec.GetAllAssetTags(TagContainer);
	EffectAssetTagsDelegate.Broadcast(TagContainer);
}
