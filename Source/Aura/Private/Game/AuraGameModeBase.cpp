// CAS Tutorial JsPalacios


#include "Game/AuraGameModeBase.h"

#include "Game/AuraGameInstance.h"
#include "Game/LoadScreenSaveGame.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ViewModel/MVVM_LoadSlot.h"

void AAuraGameModeBase::DeleteSlot(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(LoadSlot->GetLoadSlotName(),SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(LoadSlot->GetLoadSlotName(),SlotIndex);
	}
}

void AAuraGameModeBase::SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex)
{
	DeleteSlot(LoadSlot, SlotIndex);
	
	USaveGame* SaveGameObject =  UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);

	ULoadScreenSaveGame* LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject);
	LoadScreenSaveGame->PlayerName = LoadSlot->GetPlayerName();
	LoadScreenSaveGame->SaveSlotStatus = Taken;
	LoadScreenSaveGame->MapName = LoadSlot->GetMapName();
	UGameplayStatics::SaveGameToSlot(LoadScreenSaveGame,LoadSlot->GetLoadSlotName(),SlotIndex);
}

ULoadScreenSaveGame* AAuraGameModeBase::GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const
{
	if (!UGameplayStatics::DoesSaveGameExist(SlotName,SlotIndex))
	{
		return nullptr;
	}

	USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex);
	return Cast<ULoadScreenSaveGame>(SaveGameObject);
}

void AAuraGameModeBase::TravelToMap(UMVVM_LoadSlot* Slot)
{
	const FString SlotName = Slot->GetLoadSlotName();
	const int32 SlotIndex = Slot->SlotIndex;

	UGameplayStatics::OpenLevelBySoftObjectPtr(Slot, Maps.FindRef(Slot->GetMapName()));
}

AActor* AAuraGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	UAuraGameInstance* GameInstance = Cast<UAuraGameInstance>(UGameplayStatics::GetGameInstance(this));

	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	if (FoundActors.Num() == 0)
	{
		return nullptr;
	}
	
	if (FoundActors.Num() == 1)
	{
		return FoundActors[0];
	}
	
	AActor* PlayerInitStart = FoundActors[0];
	
	for (AActor* FoundActor : FoundActors)
	{
		if (APlayerStart* PlayerStart = Cast<APlayerStart>(FoundActor))
		{
			if (PlayerStart->PlayerStartTag == GameInstance->PlayerStartTag)
			{
				PlayerInitStart = PlayerStart;
				break;
			}
		}
	}

	return PlayerInitStart;
}

void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Maps.Add(StartingMapName,StartingMap);
}
