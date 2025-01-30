// CAS Tutorial JsPalacios


#include "UI/ViewModel/MVVM_LoadScreen.h"

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
		return;
	}
	
	LoadSlots[Slot]->SetPlayerName(EnteredName);
	LoadSlots[Slot]->LoadSlotStatus = Taken;
	AuraGameModeBase->SaveSlotData(LoadSlots[Slot],Slot);

	LoadSlots[Slot]->InitializeSlot();

}

void UMVVM_LoadScreen::SelectSlotButtonPressed(const int32 Slot)
{
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
		LoadSlot.Value->SetPlayerName(SaveObject->PlayerName);
		LoadSlot.Value->InitializeSlot();
	}
}
