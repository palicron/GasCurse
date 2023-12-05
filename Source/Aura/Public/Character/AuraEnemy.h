// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/IEnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IIEnemyInterface
{
	GENERATED_BODY()

public:

	AAuraEnemy();
	
	virtual void BeginPlay() override;
	
	virtual void HighlightActor() override;

	virtual void UnHighLightActor() override;

	virtual void InitAbilityActorInfo() override;
	
};
