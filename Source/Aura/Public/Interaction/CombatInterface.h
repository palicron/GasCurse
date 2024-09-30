// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"
class UNiagaraSystem;
class UAnimMontage;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnASCRegisteredSignature, UAbilitySystemComponent*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature,AActor*,DeadActor);

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MontageTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag SocketTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* ImpactSound = nullptr;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI,BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	int32 GetPlayerLevel() const;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	virtual void Die(const FVector& DeathImpulse = FVector::ZeroVector) = 0;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	AActor* GetAvatar();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	TArray<FTaggedMontage> GetAttackMontages();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UNiagaraSystem* GetBloodEffect();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FTaggedMontage GetTaggedMontageByTag(const FGameplayTag& MontageTang);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	int32 GetMinionCount();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void IncrementMinionCount(int32 Amount);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	ECharacterClass GetCharacterClass();

	virtual FOnASCRegisteredSignature GetOnASCRegisterDelegate() = 0;

	virtual FOnDeathSignature GetOnDeathDelegate() = 0;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void SetInShockLoop(const bool bInLoop);
};
