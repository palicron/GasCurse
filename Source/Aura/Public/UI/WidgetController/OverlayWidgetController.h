// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnStatusChangedSignature OnHealthChangedDelegate;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnStatusChangedSignature OnMaxHealthChangedDelegate;
	
};
