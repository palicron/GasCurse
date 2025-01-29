// CAS Tutorial JsPalacios


#include "UI/ViewModel/MVVM_LoadScreen.h"

#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadScreen::InitializeLoadSlots()
{
	LoadSlot_0 = NewObject<UMVVM_LoadSlot>(this,LoadSlotViewModelClass);
	LoadSlot_1 = NewObject<UMVVM_LoadSlot>(this,LoadSlotViewModelClass);
	LoadSlot_2 = NewObject<UMVVM_LoadSlot>(this,LoadSlotViewModelClass);

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
}

void UMVVM_LoadScreen::SelectSlotButtonPressed(const int32 Slot)
{
}
