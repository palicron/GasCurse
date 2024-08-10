// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
protected:
		
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float DebuffChance = 20.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float DebuffDamage = 5.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float DebuffFrequency = 1.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float DebuffDuration = 5.f;
	
	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTagMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
	
};
