// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "WaitCooldownChange.generated.h"


class UAbilitySystemComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoolDownChangeSignature, float, TimeRemaining);
/**
 * 
 */
UCLASS(BlueprintType , meta = (ExposedAsyncProxy = "AsyncTask"))
class AURA_API UWaitCooldownChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FCoolDownChangeSignature CoolDownStart;

	UPROPERTY(BlueprintAssignable)
	FCoolDownChangeSignature CoolDownEnd;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UWaitCooldownChange* WaitForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& InCooldownTag);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;

	FGameplayTag CooldownTag;

	UFUNCTION()
	void CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount);

	UFUNCTION()
	void OnActiveEffectAdded(UAbilitySystemComponent* TargetAsc, const FGameplayEffectSpec& EffectApply,FActiveGameplayEffectHandle ActiveEffectHandle);
};
