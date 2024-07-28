// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AuraGamePlayTags.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellGlobeSelectedSiganture,bool, bSpendPointButtonEnabled,bool,bEquipButtonEnable,const FString&,Description,const FString&,nextDescription);

struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();

	FGameplayTag Status = FGameplayTag();
};

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable)
	FSpellGlobeSelectedSiganture SpellGlobeSelectedDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatChangedSignature OnSpellPointsChangedDelegate;

	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);

	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed();

private:
	static void ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints,bool& bShouldEnableSpellPointButtons, bool& bShouldEnableEquipButtons);

	FSelectedAbility SelectedAbility = {FAuraGamePlayTags::Get().Abilities_None,FAuraGamePlayTags::Get().Abilities_Status_Locked};
	int32 CurrentSpellPoints = 0;
};
