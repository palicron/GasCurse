// CAS Tutorial JsPalacios


#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadSlot::InitializeSlot()
{
	//TODO: Check Load Status Base on data
	SetWidgetSwitcherIndexDelegate.Broadcast(1);
}
