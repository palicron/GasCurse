// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuroCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:

	AAuraCharacter();

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	TObjectPtr<USpringArmComponent> ArmSpringCompoent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	TObjectPtr<UCameraComponent> PlayerCamera;
};
