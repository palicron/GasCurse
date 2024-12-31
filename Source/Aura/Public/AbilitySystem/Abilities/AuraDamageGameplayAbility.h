// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
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

	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr,
		FVector InRadialDamageOrigin = FVector::ZeroVector, bool bOverrideKnockBackDirection = false, FVector InKnockBackDirectionDirection = FVector::ZeroVector,
		bool bOverrideDeathImpulse = false , FVector DeathImpulseOverride = FVector::ZeroVector, bool bOverridePitch = false, float PitchOverRide = 0.f) const;

	
	UFUNCTION(BlueprintPure)
	float GetDamageAtLevel() const;
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

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float DeathImpulseMagnitude = 250.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float KnockBackForceMagnitude = 250.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float KnockBackChance = 0.f;

	UPROPERTY(EditDefaultsOnly)
	bool bIsRadialDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RadialDamageInnerRadius = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RadialDamageOuterRadius = 0.f;

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTagMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
	
};
