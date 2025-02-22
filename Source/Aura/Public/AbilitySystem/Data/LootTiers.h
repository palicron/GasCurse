// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LootTiers.generated.h"

USTRUCT(BlueprintType)
struct FLootItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootTiers|Spawning")
	TSubclassOf<AActor> LootClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootTiers|Spawning")
	float ChanceToSpawn = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootTiers|Spawning")
	int32 MaxNumberToSpawn = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootTiers|Spawning")
	bool bLootLevelOverride = true;
};
/**
 * 
 */
UCLASS()
class AURA_API ULootTiers : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LootTiers|Spawning")
	TArray<FLootItem> LootItems;

	UFUNCTION(BlueprintCallable, Category = "LootTiers|Spawning")
	TArray<FLootItem> GetLootItems();
};
