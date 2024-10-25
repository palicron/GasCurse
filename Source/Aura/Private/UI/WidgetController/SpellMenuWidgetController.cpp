// CAS Tutorial JsPalacios


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraGamePlayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	OnInitilizeStarupAbilities();
	OnSpellPointsChangedDelegate.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetAuraASC()->AbilityStatusChangeDelegate.AddLambda([&](const FGameplayTag& AbilityTag,const FGameplayTag& StatusTag,const int32 AbilityLevel)
	{
		if(SelectedAbility.Ability.MatchesTagExact(AbilityTag))
		{
			SelectedAbility.Status = StatusTag;

			bool bEnableSpendPoint = false;
			bool bEnableEquip = false;

			ShouldEnableButtons(SelectedAbility.Status,CurrentSpellPoints,bEnableSpendPoint,bEnableEquip);

			FString Description;
			FString NextDescription;

			GetAuraASC()->GetDescriptionsByAbilityTag(AbilityTag,Description,NextDescription);
			SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoint,bEnableEquip,Description,NextDescription);
		}
		
		if(AbilityInfo)
		{
			FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	});

	GetAuraASC()->AbilityEquipped.AddUObject(this,&USpellMenuWidgetController::OnAbilityEquipped);
	
	GetAuraPS()->OnSpellPointChangeDelegate.AddLambda([&](int32 SpellPoints)
	{
		OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
		CurrentSpellPoints = SpellPoints;

		bool bEnableSpendPoint = false;
		bool bEnableEquip = false;

		ShouldEnableButtons(SelectedAbility.Status, CurrentSpellPoints, bEnableSpendPoint, bEnableEquip);
		FString Description;
		FString NextDescription;

		GetAuraASC()->GetDescriptionsByAbilityTag(SelectedAbility.Ability,Description,NextDescription);
		SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoint, bEnableEquip,Description,NextDescription);
	});
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{

	if(bWaitingForEquipSelection)
	{
		const FGameplayTag AbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
		StopWaitingForEquipDelegate.Broadcast(AbilityType);
		bWaitingForEquipSelection = false;
	}
	
	const FAuraGamePlayTags GameplayTags = FAuraGamePlayTags::Get();
	const int32 SpellPoints = GetAuraPS()->GetSpellPoints();
	FGameplayTag AbilityStatus;
	
	bool bTagValid = AbilityTag.IsValid();
	bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
	FGameplayAbilitySpec* AbilitySpec = GetAuraASC()->GetSpecFromAbilityTag(AbilityTag);

	if(!bTagValid || bTagNone || !AbilitySpec )
	{
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		AbilityStatus = GetAuraASC()->GetStatusFromSpec(*AbilitySpec);
	}

	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = AbilityStatus;
	
	bool bEnableSpendPoint = false;
	bool bEnableEquip = false;

	ShouldEnableButtons(AbilityStatus,SpellPoints,bEnableSpendPoint,bEnableEquip);

	FString Description;
	FString NextDescription;

	GetAuraASC()->GetDescriptionsByAbilityTag(AbilityTag,Description,NextDescription);
	SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoint, bEnableEquip,Description,NextDescription);
}

void USpellMenuWidgetController::SpendPointButtonPressed()
{
	if(!GetAuraASC())
	{
		return;
	}
	
	GetAuraASC()->Server_SpendSpellPoint(SelectedAbility.Ability);
}

void USpellMenuWidgetController::GlobeDeselect()
{
	if(bWaitingForEquipSelection)
	{
		const FGameplayTag AbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
		StopWaitingForEquipDelegate.Broadcast(AbilityType);
		bWaitingForEquipSelection = false;
	}
	
	SelectedAbility.Ability = FAuraGamePlayTags::Get().Abilities_None;
	SelectedAbility.Status = FAuraGamePlayTags::Get().Abilities_Status_Locked;
	SpellGlobeSelectedDelegate.Broadcast(false,false,FString(),FString());
	
}

void USpellMenuWidgetController::EquipButtonPressed()
{
	const FGameplayTag AbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;

	WaitForEquipDelegate.Broadcast(AbilityType);
	bWaitingForEquipSelection = true;

	const FGameplayTag SelectedStatus = GetAuraASC()->GetStatusFromAbilityTag(SelectedAbility.Ability);
	if(SelectedStatus.MatchesTagExact(FAuraGamePlayTags::Get().Abilities_Status_Equipped))
	{
		SelectedSlot = GetAuraASC()->GetSlotFromAbilityTag(SelectedAbility.Ability);
	}
}

void USpellMenuWidgetController::SpellRowGlobePressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType)
{
	if(!bWaitingForEquipSelection )
	{
		return;
	}
	//Check Selected Ability Against Slots ability type 
	const FGameplayTag SelectAbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
	if(!SelectAbilityType.MatchesTagExact(AbilityType))
	{
		return;
	}

	GetAuraASC()->Server_EquipAbility(SelectedAbility.Ability,SlotTag);
}

void USpellMenuWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,const FGameplayTag& SlotTag, const FGameplayTag& PrevSlotTag)
{
	bWaitingForEquipSelection = false;

	const FAuraGamePlayTags GameplayTags = FAuraGamePlayTags::Get();
	FAuraAbilityInfo LastSlotInfo;
	LastSlotInfo.StatusTag = GameplayTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag = PrevSlotTag;
	LastSlotInfo.AbilityTag = GameplayTags.Abilities_None;

	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = SlotTag;
	AbilityInfoDelegate.Broadcast(Info);

	StopWaitingForEquipDelegate.Broadcast(AbilityInfo->FindAbilityInfoForTag(AbilityTag).AbilityType);
	SpellGlobeReAssignedDelegate.Broadcast(AbilityTag);
	GlobeDeselect();
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpellPointButtons, bool& bShouldEnableEquipButtons)
{
	const FAuraGamePlayTags GameplayTags = FAuraGamePlayTags::Get();

	if(AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
	{
		bShouldEnableEquipButtons = true;
		if(SpellPoints>0)
		{
			bShouldEnableSpellPointButtons = true;
		}
		return;
	}

	if(AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		bShouldEnableEquipButtons = false;

		if(SpellPoints>0)
		{
			bShouldEnableSpellPointButtons = true;
		}

		return;
	}

	if(AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bShouldEnableEquipButtons = true;

		if(SpellPoints>0)
		{
			bShouldEnableSpellPointButtons = true;
		}

		return;
	}

	if(AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Locked))
	{
		bShouldEnableEquipButtons = false;
		bShouldEnableSpellPointButtons = false;
		return;
	}
}
