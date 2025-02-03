// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuroCharacter.generated.h"

class UNiagaraComponent;
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

	virtual int32 GetPlayerLevel_Implementation() const override;
	
	/*End Combat Interface*/

	/*Player Interface*/

	virtual void AddToXP_Implementation(int32 InXp) override;

	virtual void LevelUp_Implementation() override;

	virtual int32 GetCurrentXP_Implementation() const override;

	virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;

	virtual int32 GetAttributePointReward_Implementation(const int32 Level) const override;

	virtual int32 GetSpellPointsReward_Implementation(const int32 Level) const override;

	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;

	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;

	virtual int32 GetAttributePoints_Implementation() const override;

	virtual int32 GetSpellPoints_Implementation() const override;

	virtual void ShowMagicCircle_Implementation(UMaterialInterface* DecalInterface = nullptr) override;

	virtual void HideMagicCircle_Implementation() override;

	virtual void SaveProgress_Implementation(const FName& CheckPointTag) override;
	/*End Player Interface*/

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;

protected:

	virtual void OnRep_IsStunned() override;

	virtual void OnRep_IsBurned() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	TObjectPtr<USpringArmComponent> ArmSpringCompoent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	TObjectPtr<UCameraComponent> PlayerCamera;

	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;

	virtual void InitAbilityActorInfo() override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpParticles() const;

	void LoadProgress();
};
