// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IIEnemyInterface
{
	GENERATED_BODY()


public:



	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCombatTarget(AActor* InCombatTarget);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	AActor* GetCombatTarget() const;
	
};
