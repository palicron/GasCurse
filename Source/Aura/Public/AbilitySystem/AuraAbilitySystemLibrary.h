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

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static bool IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static float GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static FVector GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static FVector GetKnockBackForce(const FGameplayEffectContextHandle& EffectContextHandle);

	
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static void SetIsSuccefulDebuff(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInSuccessfulDebuff);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDamage);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDuration);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffFrquency);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static void SetDebuffType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InDeathImpulse);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GameplayEffects")
	static void SetKnockBackForce(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InForce);
	
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GamePlayMechanics")
	static void GetLifePlayerWithinRadius(const UObject* WordContextObject,TArray<AActor*>& OutOverLappingActors, const TArray<AActor*>& ActorsToIgnore,float Radius,const FVector& SphereOrigin);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GamePlayMechanics")
	static void GetClosestTargets(const int32 MaxTargets, const TArray<AActor*>& Actors, TArray<AActor*>& OutClosestTargets, const FVector& Origin);
	
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySytemLibrary|GamePlayMechanics")
	static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySytemLibrary|GamePlayMechanics")
	static int32 GetXPRewardForClassAndLevel(const UObject* WordContextObject, ECharacterClass CharacterClass, int32 CharacterLevel);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySytemLibrary|CharacterClassDefaults")
	static UAbilityInfo* GetAbilityInfo(const UObject* WordContextObject);

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySytemLibrary|CharacterClassDefaults")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams DamageEffectParams);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySytemLibrary|Math")
	static TArray<FRotator> EvenlySpaceRotators(const FVector& Forward, const FVector& Axis, const float Spread, const int32 NumRotator);

	UFUNCTION(BlueprintPure,Category="AuraAbilitySytemLibrary|Math")
	static TArray<FVector> EvenlyRotateVectors(const FVector& Forward, const FVector& Axis, const float Spread, const int32 NumVectors);
};
