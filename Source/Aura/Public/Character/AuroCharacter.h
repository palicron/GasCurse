// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuroCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()

public:

	AAuraCharacter();

	/*Combat Interface*/

	virtual int32 GetPlayerLevel() const override;
	
	/*End Combat Interface*/

	/*Player Interface*/

	virtual void AddToXP_Implementation(int32 InXp) override;
	/*End Player Interface*/

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	TObjectPtr<USpringArmComponent> ArmSpringCompoent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	TObjectPtr<UCameraComponent> PlayerCamera;

	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;

	virtual void InitAbilityActorInfo() override;
};
