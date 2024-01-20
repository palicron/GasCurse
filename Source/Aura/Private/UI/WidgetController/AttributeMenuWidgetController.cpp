// CAS Tutorial JsPalacios


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGamePlayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttribute)
	{
		BrodcastAttributeInfo(Pair.Key,Pair.Value());
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	for (auto& Pair : AS->TagsToAttribute)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this,Pair](const FOnAttributeChangeData& Data)
			{
				BrodcastAttributeInfo(Pair.Key,Pair.Value());
			});
	}
	
}

void UAttributeMenuWidgetController::BrodcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const 
{
	FAuraAttributeInfo info =  AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(info);
}
