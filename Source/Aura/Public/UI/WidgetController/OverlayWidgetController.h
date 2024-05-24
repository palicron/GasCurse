// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"


struct FAuraAbilityInfo;
class UAuraAbilitySystemComponent;
class UAbilityInfo;
class UAuraUserWidget;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusChangedSignature, float, NewSatus);


USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetRow, Row);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature,const FAuraAbilityInfo&,Info);
/**
 *																			
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadcastInitialValues() override;
	
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnStatusChangedSignature OnHealthChangedDelegate;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnStatusChangedSignature OnMaxHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnStatusChangedSignature OnManaChangedDelegate;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnStatusChangedSignature OnMaxManaChangedDelegate;

	UPROPERTY(BlueprintAssignable,Category="GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

	UPROPERTY(BlueprintAssignable,Category="GAS|Messages")
	FAbilityInfoSignature AbilityInfoDelegate;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|XP")
	FOnStatusChangedSignature OnXPPercentChangedDelegate;
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widget Data")
	TObjectPtr<UAbilityInfo> AbilityInfo;
	
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;

	void ManaChanged(const FOnAttributeChangeData& Data) const;
	
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;

	template<typename T> T* GetDataTableRowByTag(UDataTable* DataTable, const  FGameplayTag& Tag);
	
	void OnInitilizeStarupAbilities(UAuraAbilitySystemComponent* AuraASC);

	void OnXPChange(int32 NewXP) const;
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
