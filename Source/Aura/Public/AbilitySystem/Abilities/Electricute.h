// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraBeamSpell.h"
#include "Electricute.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UElectricute : public UAuraBeamSpell
{
	GENERATED_BODY()

public:

	virtual FString GetDescription(const int32 Level) const override;

	virtual FString GetNextLevelDescription(const int32 Level) const override;
	
};
