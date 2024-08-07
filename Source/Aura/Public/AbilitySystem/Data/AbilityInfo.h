// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityInfo.generated.h"



USTRUCT(BlueprintType)
struct FAuraAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag StatusTag = FGameplayTag();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTag CooldownTag = FGameplayTag();
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTag AbilityType = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<const UTexture2D> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<const UMaterialInterface> BackGroundMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 LevelRequirement = 1;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> Ability;
	
};
/**
 * 
 */
UCLASS()
class AURA_API UAbilityInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category= "Ability Information")
	TMap<FGameplayTag,FAuraAbilityInfo> AbilityInformation;

	
	FAuraAbilityInfo FindAbilityInfoForTag(const FGameplayTag AbilityTag,bool bLogNotFound = false) const;
};
