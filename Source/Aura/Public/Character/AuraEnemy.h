// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/HighlightInterface.h"
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
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IIEnemyInterface, public IHighlightInterface
{
	GENERATED_BODY()

public:

	AAuraEnemy();

	/*Combat Interface*/
	virtual int32 GetPlayerLevel_Implementation() const;
	virtual void Die(const FVector& DeathImpulse) override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/*End Combat interface*/
	
	virtual void BeginPlay() override;
	
	virtual void HighlightActor_Implementation() override;

	virtual void UnHighLightActor_Implementation() override;

	virtual void InitAbilityActorInfo() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void SetMoveToLocation_Implementation(FVector& OutDestination) override;

	UPROPERTY(BlueprintAssignable)	
	FOnStatusChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)	
	FOnStatusChangedSignature OnMaxHealthChanged;

	UFUNCTION()
	void HitReactTagChange(const FGameplayTag CallBackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly , Category= "Combat")
	bool bHitReacting = false;
	
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

	virtual void StunTagChanged(const FGameplayTag CallbackTag, const int32 NewCount) override;
};

inline void AAuraEnemy::SetMoveToLocation_Implementation(FVector& OutDestination)
{
	
}
