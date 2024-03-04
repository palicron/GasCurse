#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext: public FGameplayEffectContext
{
	GENERATED_BODY()

	
public:
	bool IsCriticalHit() const {return bIsCriticalHit;}
	bool IsBlockHit() const {return bIsBlockHit;}

	void SetIsCriticalHit(const bool bInCriticalHit) { bIsCriticalHit = bInCriticalHit; }
	void SetIsBlockHit(const bool bInIsBlockHit) { bIsCriticalHit = bInIsBlockHit; }

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