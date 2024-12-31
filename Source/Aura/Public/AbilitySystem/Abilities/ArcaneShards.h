// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "ArcaneShards.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UArcaneShards : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

public:

	virtual FString GetDescription(const int32 Level) const override;

	virtual FString GetNextLevelDescription(const int32 Level) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Arcane Shards")
	int32 MaxNumbShards = 11;
};
