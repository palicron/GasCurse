// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure,Category="Summoning")
	TSubclassOf<APawn> GetRandomMinionClass();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Summoning")
	int32 NumMinions = 5;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Summoning")
	float MinSpawnDistance = 80.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Summoning")
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Summoning")
	float SpawnSpread = 90.f;


};
