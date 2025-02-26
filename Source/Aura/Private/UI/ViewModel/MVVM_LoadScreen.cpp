// CAS Tutorial JsPalacios


#include "UI/ViewModel/MVVM_LoadScreen.h"

#include "Game/AuraGameInstance.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadScreen::InitializeLoadSlots()
{
	LoadSlot_0 = NewObject<UMVVM_LoadSlot>(this,LoadSlotViewModelClass);
	LoadSlot_1 = NewObject<UMVVM_LoadSlot>(this,LoadSlotViewModelClass);
	LoadSlot_2 = NewObject<UMVVM_LoadSlot>(this,LoadSlotViewModelClass);

	LoadSlot_0->SetLoadSlotName(FString("LoadSlot_0"));
	LoadSlot_1->SetLoadSlotName(FString("LoadSlot_1"));
	LoadSlot_2->SetLoadSlotName(FString("LoadSlot_2"));

	LoadSlot_0->SlotIndex = 0;
	LoadSlot_1->SlotIndex = 1;
	LoadSlot_2->SlotIndex = 2;
	
	LoadSlots.Add(0,LoadSlot_0);
	LoadSlots.Add(1,LoadSlot_1);
	LoadSlots.Add(2,LoadSlot_2);
}

UMVVM_LoadSlot* UMVVM_LoadScreen::GetLoadSlotViewModelByIndex(const int32 Index) const
{
	return LoadSlots.FindRef(Index);
}

void UMVVM_LoadScreen::NewGameButtonPressed(const int32 Slot)
{
	LoadSlots[Slot]->SetWidgetSwitcherIndexDelegate.Broadcast(1);
}

void UMVVM_LoadScreen::NewSlotButtonPressed(const int32 Slot, const FString& EnteredName)
{
	AAuraGameModeBase* AuraGameModeBase = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (!AuraGameModeBase || EnteredName.IsEmpty())
	{
		if (GEngine)
		GEngine->AddOnScreenDebugMessage(1,15.f,FColor::Red,"PLease Switch to single player");
		return;
	}
	LoadSlots[Slot]->SetMapName(AuraGameModeBase->StartingMapName);
	LoadSlots[Slot]->SetPlayerName(EnteredName);
	LoadSlots[Slot]->LoadSlotStatus = Taken;
	LoadSlots[Slot]->SetPlayerLevel(1);
	LoadSlots[Slot]->PlayerStartTag =  AuraGameModeBase->DefaultPlayerStartTag;
	
	LoadSlots[Slot]->MapAssetName = AuraGameModeBase->StartingMap.ToSoftObjectPath().GetAssetName();
	
	AuraGameModeBase->SaveSlotData(LoadSlots[Slot],Slot);

	LoadSlots[Slot]->InitializeSlot();

	UAuraGameInstance* GameInstance = Cast<UAuraGameInstance>(UGameplayStatics::GetGameInstance(this)); 
	GameInstance->LoadSlot = LoadSlots[Slot]->GetLoadSlotName();
	GameInstance->LoadSlotIndex = LoadSlots[Slot]->SlotIndex;
	GameInstance->PlayerStartTag = AuraGameModeBase->DefaultPlayerStartTag;
}

void UMVVM_LoadScreen::SelectSlotButtonPressed(const int32 Slot)
{
	SlotSelectedDelegate.Broadcast();
	
	for (const TTuple<int32,UMVVM_LoadSlot*>& LoadSlot : LoadSlots)
	{
		LoadSlot.Value->EnableSelectSlotButtonDelegate.Broadcast(Slot != LoadSlot.Key);
	}

	CurrentSlot = Slot;
}

void UMVVM_LoadScreen::DeleteButtonPressed()
{
	AAuraGameModeBase* AuraGameModeBase = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (AuraGameModeBase)
	{
		AuraGameModeBase->DeleteSlot(LoadSlots[CurrentSlot],CurrentSlot);
		LoadSlots[CurrentSlot]->LoadSlotStatus = Vacant;
		LoadSlots[CurrentSlot]->InitializeSlot();
		LoadSlots[CurrentSlot]->EnableSelectSlotButtonDelegate.Broadcast(true);
	}
}

void UMVVM_LoadScreen::PlayButtonPressed()
{
	AAuraGameModeBase* AuraGameModeBase = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!AuraGameModeBase)
	{
		return;
	}
	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(AuraGameModeBase->GetGameInstance());
	if (!AuraGameInstance)
	{
		return;
	}
	AuraGameInstance->PlayerStartTag = LoadSlots[CurrentSlot]->PlayerStartTag;
	AuraGameInstance->LoadSlot = LoadSlots[CurrentSlot]->GetLoadSlotName();
	AuraGameInstance->LoadSlotIndex = LoadSlots[CurrentSlot]->SlotIndex;
	AuraGameModeBase->TravelToMap(LoadSlots[CurrentSlot]);
}

void UMVVM_LoadScreen::LoadData()
{
	AAuraGameModeBase* AuraGameModeBase = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (!AuraGameModeBase)
	{
		return;
	}
	
	for (const TTuple<int32,UMVVM_LoadSlot*>& LoadSlot : LoadSlots)
	{
		ULoadScreenSaveGame* SaveObject = AuraGameModeBase->GetSaveSlotData(LoadSlot.Value->GetLoadSlotName(),LoadSlot.Key);

		if (!SaveObject)
		{
			continue;
		}
		LoadSlot.Value->LoadSlotStatus = SaveObject->SaveSlotStatus;
		LoadSlot.Value->SetPlayerLevel(SaveObject->PlayerLevel);
		LoadSlot.Value->SetMapName(SaveObject->MapName);
		LoadSlot.Value->SetPlayerName(SaveObject->PlayerName);
		LoadSlot.Value->PlayerStartTag = SaveObject->PlayerStartTag;
		LoadSlot.Value->MapAssetName = SaveObject->MapAssetName;
		LoadSlot.Value->InitializeSlot();
		
	}
}
