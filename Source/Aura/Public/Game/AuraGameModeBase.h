// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class ULoadScreenSaveGame;
class USaveGame;
class UMVVM_LoadSlot;
class UAbilityInfo;
class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly,Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly,Category="Ability Info")
	TObjectPtr<UAbilityInfo> AbilityInfo;

	void DeleteSlot(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex);
	void SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex);

	UPROPERTY(EditDefaultsOnly,Category="SaveSlot")
	TSubclassOf<USaveGame> LoadScreenSaveGameClass;
	
	UFUNCTION()
	ULoadScreenSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const;

	UPROPERTY(EditDefaultsOnly,Category="Maps")
	FString StartingMapName;
	
	UPROPERTY(EditDefaultsOnly,Category="Maps")
	FName DefaultPlayerStartTag;
	
	UPROPERTY(EditDefaultsOnly,Category="Maps")
	TSoftObjectPtr<UWorld> StartingMap;
	
	UPROPERTY(EditDefaultsOnly,Category="Maps")
	TMap<FString,TSoftObjectPtr<UWorld>> Maps;

	void TravelToMap(UMVVM_LoadSlot* Slot);
	
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	ULoadScreenSaveGame* RetrieveInGameSaveData() const;

	void SaveInGameProgressData(ULoadScreenSaveGame* SaveObject);

	void SaveWorldState(UWorld* World);
protected:
	virtual void BeginPlay() override;
};
