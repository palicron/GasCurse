// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraAbilitySystemLibrary.generated.h"

class AAuraHUD;
class USpellMenuWidgetController;
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

	UFUNCTION(BlueprintPure,Category="AuraAbilitySytemLibrary|WidgetController", meta=(DefaultToSelf = "WordContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WordContextObject,FWidgetControllerParams& outWCParams, AAuraHUD*& OutAuraHud);
	
	UFUNCTION(BlueprintPure,Category="AuraAbilitySytemLibrary|WidgetController",meta=(DefaultToSelf = "WordContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WordContextObject);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySytemLibrary|WidgetController",meta=(DefaultToSelf = "WordContextObject"))
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WordContextObject);
	
	UFUNCTION(BlueprintPure,Category="AuraAbilitySytemLibrary|WidgetController",meta=(DefaultToSelf = "WordContextObject"))
	static USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WordContextObject);
	
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

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GamePlayMechanics")
	static void GetLifePlayerWithinRadius(const UObject* WordContextObject,TArray<AActor*>& OutOverLappingActors, const TArray<AActor*>& ActorsToIgnore,float Radius,const FVector& SphereOrigin);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySytemLibrary|GamePlayMechanics")
	static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GamePlayMechanics")
	static int32 GetXPRewardForClassAndLevel(const UObject* WordContextObject, ECharacterClass CharacterClass, int32 CharacterLevel);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySytemLibrary|CharacterClassDefaults")
	static UAbilityInfo* GetAbilityInfo(const UObject* WordContextObject);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySytemLibrary|CharacterClassDefaults")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams DamageEffectParams);
};
