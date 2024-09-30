// CAS Tutorial JsPalacios

#pragma once
#include "GameplayTagContainer.h"

struct FGameplayAbilitySpec;
class UAuraAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAsseTagSignature, const FGameplayTagContainer& /* AssetTags*/);
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChangeSignature,const FGameplayTag&/* AbilityTag*/,const FGameplayTag& /**Status change*/,const int32 /*Level*/)
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquippedSignarture,const FGameplayTag& /* AbilityTag*/,const FGameplayTag& /* Status Tag*/,const FGameplayTag& /* Slot Tag*/,const FGameplayTag& /* PreSlotsTag*/)
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

	FAbilityStatusChangeSignature AbilityStatusChangeDelegate;

	FAbilityEquippedSignarture AbilityEquipped;
	
	uint8 bStartupAbilitiesGiven : 1;
 

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> StartupAbilities);

	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	
	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ForEachAbility(const FForEachAbility& Delegate);

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	void UpgradeAttributes(const FGameplayTag& AttributeTag);

	UFUNCTION(Server,Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);

	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	FGameplayTag GetStatusFromAbilityTag(const FGameplayTag& AbilityTag);

	FGameplayTag GetInputTagFromAbilityTag(const FGameplayTag& AbilityTag);

	void UpdateAbilityStatus(int32 Level);

	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);

	UFUNCTION(Server,Reliable)
	void Server_SpendSpellPoint(const FGameplayTag& AbilityTag);

	UFUNCTION(Server,Reliable)
	void Server_EquipAbility(const FGameplayTag& AbilityTag,const FGameplayTag& SlotTag);

	UFUNCTION(Client,Reliable)
	void Client_EquipAbility(const FGameplayTag& AbilityTag,const FGameplayTag& Status,const FGameplayTag& SlotTag,const FGameplayTag& PreviusSlot);
	
	bool GetDescriptionsByAbilityTag(const FGameplayTag& AbilityTag,FString& OutDescription,FString& OutNextLeventDescription);

	void ClearSlot(FGameplayAbilitySpec* Spec);

	void ClearAbilitiesOfSlot(const FGameplayTag& SlotTag);

	static bool AbilityHasSlot(FGameplayAbilitySpec* Spec,const FGameplayTag& SlotTag);

protected:

	UFUNCTION(Client,Reliable)
	void Client_EffectApplied(UAbilitySystemComponent* AbilitySystemComp, const FGameplayEffectSpec& GamePlaySpec, FActiveGameplayEffectHandle ActiveHandel);

	virtual void OnRep_ActivateAbilities() override;

	UFUNCTION(Client,Reliable)
	void ClientUpdateAbilityStatus(const FGameplayTag& AbilityTag,const FGameplayTag& StatusChange,const int32 AbilityLevel);
	
};
