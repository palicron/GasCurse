// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusChangedSignature, float , NewSatus);

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

protected:

	
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;

	void ManaChanged(const FOnAttributeChangeData& Data) const;
	
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
	
};
