// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/IEnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AAuraAIController;
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
	virtual void Die() override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/*End Combat interface*/
	
	virtual void BeginPlay() override;
	
	virtual void HighlightActor() override;

	virtual void UnHighLightActor() override;

	virtual void InitAbilityActorInfo() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintAssignable)	
	FOnStatusChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)	
	FOnStatusChangedSignature OnMaxHealthChanged;

	UFUNCTION()
	void HitReactTagChange(const FGameplayTag CallBackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly , Category= "Combat")
	bool bHitReacting = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , Category= "Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly , Category= "Combat")
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor> CombatTarget;
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere,Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
	
};
