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

	/*Combat Interface*/
	virtual int32 GetPlayerLevel() const override;
	/*End Combat interface*/
	
	virtual void BeginPlay() override;
	
	virtual void HighlightActor() override;

	virtual void UnHighLightActor() override;

	virtual void InitAbilityActorInfo() override;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;
	
};
