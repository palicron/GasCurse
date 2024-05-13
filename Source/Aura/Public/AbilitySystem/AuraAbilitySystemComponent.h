// CAS Tutorial JsPalacios

#pragma once
#include "GameplayTagContainer.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAsseTagSignature, const FGameplayTagContainer& /* AssetTags*/)
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven, UAuraAbilitySystemComponent*);
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

	FAbilitiesGiven AbilitiesGivenDelegate;

	uint8 bStartupAbilitiesGiven : 1;
 

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> StartupAbilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	
	
protected:

	UFUNCTION(Client,Reliable)
	void Client_EffectApplied(UAbilitySystemComponent* AbilitySystemComp, const FGameplayEffectSpec& GamePlaySpec, FActiveGameplayEffectHandle ActiveHandel);
	
};
