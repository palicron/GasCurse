// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure,Category="AuraAbilitySytemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WordContextObject);
	
};
