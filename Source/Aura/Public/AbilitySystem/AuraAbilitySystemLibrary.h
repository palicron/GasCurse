// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAbilitySystemComponent;
class UAttributeMenuWidgetController;
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

	UFUNCTION(BlueprintPure,Category="AuraAbilitySytemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WordContextObject);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySytemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WordContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);
};
