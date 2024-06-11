// CAS Tutorial JsPalacios


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	
	
	OnHealthChangedDelegate.Broadcast(GetAuraAS()->GetHealth());
	OnMaxHealthChangedDelegate.Broadcast(GetAuraAS()->GetMaxHealth());
	OnManaChangedDelegate.Broadcast(GetAuraAS()->GetMana());
	OnMaxManaChangedDelegate.Broadcast(GetAuraAS()->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	GetAuraPS()->OnXpChangeDelegate.AddUObject(this,&UOverlayWidgetController::OnXPChange);
	GetAuraPS()->OnLevelChangeDelegate.AddLambda([&] (int32 LevelChange)
	{
		OnPlayerLevelChangeDelegate.Broadcast(LevelChange);
	});

	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetHealthAttribute()).AddUObject(
		this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetMaxHealthAttribute()).AddUObject(
		this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetManaAttribute()).AddUObject(
	this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetMaxManaAttribute()).AddUObject(
	this, &UOverlayWidgetController::MaxManaChanged);

	if (GetAuraASC())
	{
		if (GetAuraASC()->bStartupAbilitiesGiven)
		{
			OnInitilizeStarupAbilities(GetAuraASC());
		}
		else
		{
			GetAuraASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitilizeStarupAbilities);
		}
		GetAuraASC()->EffectAssetTagsDelegate.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						if (const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag))
						{
							MessageWidgetRowDelegate.Broadcast(*Row);
						}
					}
				}
			});
	}
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChangedDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnMaxHealthChangedDelegate.Broadcast(AuraAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChangedDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnMaxManaChangedDelegate.Broadcast(AuraAttributeSet->GetMaxMana());
}


void UOverlayWidgetController::OnXPChange(int32 NewXP) const
{
	const AAuraPlayerState* CurrePlayerstate = CastChecked<AAuraPlayerState>(PlayerState);
	const ULevelUpInfo* LevelUpInfo = CurrePlayerstate->LevelUpInfo;

	checkf(LevelUpInfo,TEXT("NO Level Up inof in player state"));

	const int32 Level = LevelUpInfo->FindLevelForXp(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInfos.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInfos[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInfos[Level - 1].LevelUpRequirement;


		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XpForThisLevel = (NewXP - PreviousLevelUpRequirement);
		float XPBarPercent = static_cast<float>(XpForThisLevel)/ static_cast<float>(DeltaLevelRequirement);
		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
}
