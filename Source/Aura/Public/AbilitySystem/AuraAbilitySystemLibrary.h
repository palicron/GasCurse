// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

struct FGameplayEffectContextHandle;
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

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySytemLibrary|CharacterClassDefaults")
	static void GiveStartUpAbilities(const UObject* WordContextObject,UAbilitySystemComponent* ASC,ECharacterClass CharacterClass);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySytemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WordContextObject);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySytemLibrary|GameplayEffects") 
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);
};
