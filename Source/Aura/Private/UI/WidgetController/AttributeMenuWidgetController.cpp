// CAS Tutorial JsPalacios


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttribute)
	{
		BrodcastAttributeInfo(Pair.Key,Pair.Value());
	}
	AAuraPlayerState* CurrePlayerstate = CastChecked<AAuraPlayerState>(PlayerState);

	AttributePointsChangedDelegate.Broadcast(CurrePlayerstate->GetAttributePoints());
	SpellPointsChangedDelegate.Broadcast(CurrePlayerstate->GetSpellPoints());
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

	AAuraPlayerState* CurrePlayerstate = CastChecked<AAuraPlayerState>(PlayerState);
	CurrePlayerstate->OnAttributePointChangeDelegate.AddLambda([&](int32 InPoints)
	{
		AttributePointsChangedDelegate.Broadcast(InPoints);
	});
	CurrePlayerstate->OnSpellPointChangeDelegate.AddLambda([&](int32 InPoints)
	{
		SpellPointsChangedDelegate.Broadcast(InPoints);
	});
}

void UAttributeMenuWidgetController::UpgradeAttributes(const FGameplayTag& AttributeTag)
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->UpgradeAttributes(AttributeTag);
}

void UAttributeMenuWidgetController::BrodcastAttributeInfo(const FGameplayTag& AttributeTag,
                                                           const FGameplayAttribute& Attribute) const 
{
	FAuraAttributeInfo info =  AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(info);
}
