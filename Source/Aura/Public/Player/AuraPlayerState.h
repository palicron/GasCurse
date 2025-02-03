// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;
class UAttributeSet;
class UAuraAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FAuraOnStateChangeSignature,int32 /*StateValue*/);
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	
	FAuraOnStateChangeSignature OnXpChangeDelegate;

	FAuraOnStateChangeSignature OnLevelChangeDelegate;

	FAuraOnStateChangeSignature OnAttributePointChangeDelegate;

	FAuraOnStateChangeSignature OnSpellPointChangeDelegate;
	
	int32 GetPlayerXP() const { return PlayerXP;}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;
	
	void SetXP(const int32 NewXP);

	void AddToXP(const int32 NewXP);

	void SetLevel(const int32 Newlevel);

	void AddToLevel(const int32 Newlevel);

	void AddToAttributePoints(int32 InPoints);

	void AddToSpellPoints(int32 InPoints);

	void SetAttributePoint(const int32 InPoints);

	void SetSpellPoint(const int32 InPoints);
	
	UFUNCTION(BlueprintCallable)
	int32 GetAttributePoints() const {return AttributePoints;}

	UFUNCTION(BlueprintCallable)
	int32 GetSpellPoints() const {return SpellPoints;}

protected:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerXP)
	int32 PlayerXP;

	UFUNCTION()
	void OnRep_PlayerXP();

private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_AttributePoints)
	int32 AttributePoints = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SpellPoints)
	int32 SpellPoints = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributesPoint);

	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);
	
};
