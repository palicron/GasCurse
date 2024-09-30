// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "AuraFireBolt.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraFireBolt : public UAuraProjectileSpell
{
	GENERATED_BODY()

public:
	
	virtual FString GetDescription(const int32 Level) const override;

	virtual FString GetNextLevelDescription(const int32 Level) const override;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,const bool bPitchOverRide, const float PitchOverRide, const AActor* HomingTarget);

protected:

	UPROPERTY(EditDefaultsOnly, Category="Firebolt")
	int32 MaxNumProjectile = 5;
	
	UPROPERTY(EditDefaultsOnly, Category="Firebolt")
	float ProjectileSpread = 90.f;

	UPROPERTY(EditDefaultsOnly, Category="Firebolt")
	float HomingAccelerationMin = 1600.f;

	UPROPERTY(EditDefaultsOnly, Category="Firebolt")
	float HomingAccelerationMax = 3200.f;

	UPROPERTY(EditDefaultsOnly, Category="Firebolt")
	bool bLaunchHomingProjectiles = true;
};
