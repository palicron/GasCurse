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

	virtual void HighlightActor() = 0;

	virtual void UnHighLightActor() = 0;

	
};
