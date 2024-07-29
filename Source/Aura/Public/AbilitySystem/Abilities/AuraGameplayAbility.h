// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly,Category="Input")
	FGameplayTag StartupInputTag;

	virtual FString GetDescription(const int32 Level) const;
	
	virtual FString GetNextLevelDescription(const int32 Level) const;

	static  FString GetLockDescription(const int32 Level);

protected:

	float GetManaCost(float InLevel = 1.f) const;
	
	float GetCoolDown(float InLevel = 1.f) const;
};
