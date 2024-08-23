#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams(){}

	UPROPERTY()
	TObjectPtr<UObject> WorldContextObject = nullptr;

	UPROPERTY()
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;

	UPROPERTY()
	float BaseDamage = 0.f;

	UPROPERTY()
	float AbilityLevel = 1.f;

	UPROPERTY()
	FGameplayTag DamageType = FGameplayTag();

	UPROPERTY()
	float DebuffChance = 0.f;

	UPROPERTY()
	float DebuffDamage = 0.f;

	UPROPERTY()
	float DebuffDuration = 0.f;

	UPROPERTY()
	float DebuffFrequency = 0.f;
	
};

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext: public FGameplayEffectContext
{
	GENERATED_BODY()

	
public:
	bool IsCriticalHit() const {return bIsCriticalHit;}
	bool IsBlockHit() const {return bIsBlockHit;}
	bool IsSuccessfulDebuff() const {return bIsSuccessfulDebuff;}
	float GetDebuffDamage() const {return DebuffDamage;}
	float GetDebuffDuration() const {return DebuffDuration;}
	float GetDebuffFrecuency() const {return DebuffFrequency;}
	TSharedPtr<FGameplayTag> GetDamageType() const { return DamageType;}

	void SetIsSuccessfulDebuff(bool bInDebuff) { bIsSuccessfulDebuff = bInDebuff;}
	void SetIsDebuffDamage(bool bInDamage) { DebuffDamage = bInDamage;}
	void SetDebuffDuration(bool bInDuration) { DebuffDuration = bInDuration;}
	void SetDebuffFrecuency(bool bInFrecuency) { DebuffFrequency = bInFrecuency;}
	void SetDamageTypes(TSharedPtr<FGameplayTag> InDamageType) { DamageType = InDamageType;};
	
	void SetIsCriticalHit(const bool bInCriticalHit) { bIsCriticalHit = bInCriticalHit; }
	void SetIsBlockHit(const bool bInIsBlockHit) { bIsBlockHit = bInIsBlockHit; }

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FAuraGameplayEffectContext* Duplicate() const
	{
		FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayEffectContext::StaticStruct();
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;
protected:
	

	UPROPERTY()
	bool bIsBlockHit = false;
	
	UPROPERTY()
	bool bIsCriticalHit = false;

	UPROPERTY()
	bool bIsSuccessfulDebuff = false;

	UPROPERTY()
	float DebuffDamage = 0.f;

	UPROPERTY()
	float DebuffDuration = 0.f;

	UPROPERTY()
	float DebuffFrequency = 0.f;

	TSharedPtr<FGameplayTag> DamageType;
};

template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithCopy = true,		// Necessary so that TSharedPtr<FGameplayEffectContext> Data is copied around
		WithNetSerializer = true,
	};
};