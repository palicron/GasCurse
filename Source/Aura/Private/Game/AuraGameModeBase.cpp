// CAS Tutorial JsPalacios


#include "Game/AuraGameModeBase.h"

#include "EngineUtils.h"
#include "Game/AuraGameInstance.h"
#include "Game/LoadScreenSaveGame.h"
#include "GameFramework/PlayerStart.h"
#include "Interaction/SaveInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
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
	LoadScreenSaveGame->PlayerStartTag = LoadSlot->PlayerStartTag;
	
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

ULoadScreenSaveGame* AAuraGameModeBase::RetrieveInGameSaveData() const
{
	const UAuraGameInstance* AuraGameInstance	= Cast<UAuraGameInstance>(GetGameInstance());

	const FString InGameSlotName = AuraGameInstance->LoadSlot;
	const int32 InGameSlotIndex = AuraGameInstance->LoadSlotIndex;

	return GetSaveSlotData(InGameSlotName, InGameSlotIndex);
}

void AAuraGameModeBase::SaveInGameProgressData(ULoadScreenSaveGame* SaveObject)
{
	UAuraGameInstance* AuraGameInstance	= Cast<UAuraGameInstance>(GetGameInstance());
	
	const FString InGameSlotName = AuraGameInstance->LoadSlot;
	const int32 InGameSlotIndex = AuraGameInstance->LoadSlotIndex;

	AuraGameInstance->PlayerStartTag = SaveObject->PlayerStartTag;
	SaveObject->bFirstTimeLoadIn = false;
	UGameplayStatics::SaveGameToSlot(SaveObject, InGameSlotName, InGameSlotIndex);
}

void AAuraGameModeBase::SaveWorldState(UWorld* World)
{
	FString WorldName = World->GetMapName();
	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);

	UAuraGameInstance* AuraGI = Cast<UAuraGameInstance>(GetGameInstance());

	if (ULoadScreenSaveGame* SaveGame = GetSaveSlotData(AuraGI->LoadSlot, AuraGI->LoadSlotIndex))
	{
		if (!SaveGame->HasMap(WorldName))
		{
			FSaveMap NewSaveMap;
			NewSaveMap.MapAssetName = WorldName;
			SaveGame->SaveMap.Add(NewSaveMap);
		}

		FSaveMap SaveMap = SaveGame->GetSaveMapWhitMapName(WorldName);
		SaveMap.Actors.Empty();
	
		for (FActorIterator It(World);It; ++It)
		{
			AActor* Actor = *It;
			if (!IsValid(Actor) || !Actor->Implements<USaveInterface>())
			{
				continue;
			}

			FSaveActor SaveActor;
			SaveActor.ActorName = Actor->GetFName();
			SaveActor.ActorTransform = Actor->GetActorTransform();

			FMemoryWriter MemoryWriter(SaveActor.Bytes);

			FObjectAndNameAsStringProxyArchive Archive(MemoryWriter,true);
			Archive.ArIsSaveGame = true;
			Actor->Serialize(Archive);

			SaveMap.Actors.AddUnique(SaveActor);
		}

		for (FSaveMap& MapToReplace : SaveGame->SaveMap)
		{
			if (MapToReplace.MapAssetName == WorldName )
			{
				MapToReplace = SaveMap;
			}
		}

		UGameplayStatics::SaveGameToSlot(SaveGame,AuraGI->LoadSlot, AuraGI->LoadSlotIndex);
	}
}

void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Maps.Add(StartingMapName,StartingMap);
}
