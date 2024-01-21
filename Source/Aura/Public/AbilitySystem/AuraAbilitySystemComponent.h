// CAS Tutorial JsPalacios

#pragma once
#include "GameplayTagContainer.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAsseTagSignature, const FGameplayTagContainer& /* AssetTags*/)
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

	FEffectAsseTagSignature EffectAssetTagsDelegate;

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> StartupAbilities);
	
protected:

	void EffectApplied(UAbilitySystemComponent* AbilitySystemComp, const FGameplayEffectSpec& GamePlaySpec, FActiveGameplayEffectHandle ActiveHandel);
	
};
