// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameplayTags.h"
#include "Abilities/GameplayAbility.h"
#include "LoadScreenSaveGame.generated.h"

UENUM(BlueprintType)
enum ESaveLoadStatus
{
	Vacant,
	EnterName,
	Taken
};

USTRUCT(BlueprintType)
struct FSaveAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveGame")
	TSubclassOf<UGameplayAbility> GameplayAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveGame")
	FGameplayTag AbilityTag = FGameplayTag();

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveGame")
	FGameplayTag StatusAbilityTag = FGameplayTag();

		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveGame")
	FGameplayTag AbilitySlot = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveGame")
	FGameplayTag AbilityType = FGameplayTag();


	int32 AbilityLevel = 1;

	bool operator==(const FSaveAbility& In) const
	{
		return AbilityTag.MatchesTagExact(In.AbilityType);
	}
};
/**
 * 
 */

UCLASS()
class AURA_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	FString SlotName = FString("");

	UPROPERTY()
	int32 SlotIndex = 0;

	UPROPERTY()
	FString PlayerName = FString("Default Name");

	UPROPERTY()
	FString MapName = FString("Default Map");

	UPROPERTY()
	TEnumAsByte<ESaveLoadStatus> SaveSlotStatus = Vacant;

	UPROPERTY()
	FName PlayerStartTag;

	UPROPERTY()
	bool bFirstTimeLoadIn = true;

	/*Player*/

	UPROPERTY()
	int32 PlayerLevel = 1;
 
	UPROPERTY()
	int32 PlayerXP = 0;

	UPROPERTY()
	int32 SpellPoints = 0;

	UPROPERTY()
	int32 AttributePoints = 0;

	UPROPERTY()
	float Strength = 0;

	UPROPERTY()
	float Intelligence = 0;

	UPROPERTY()
	float Resilience = 0;

	UPROPERTY()
	float Vigor = 0;

	/*Abilities*/

	UPROPERTY()
	TArray<FSaveAbility> SaveAbilities;
	
};
