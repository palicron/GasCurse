// CAS Tutorial JsPalacios


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGamePlayTags.h"
void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);

	FAuraAttributeInfo info = AttributeInfo->FindAttributeInfoForTag(FAuraGamePlayTags::Get().Attributes_Primary_Strength);
	info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(info);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{

	
}
