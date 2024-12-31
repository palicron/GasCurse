// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraFireBlast.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraFireBlast : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

public:
	
	virtual FString GetDescription(const int32 Level) const override;

	virtual FString GetNextLevelDescription(const int32 Level) const override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Ability", meta=(AllowPrivateAccess=true))
	int32 NumFireBalls = 12;

	
};
