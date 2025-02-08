// CAS Tutorial JsPalacios


#include "AbilitySystem/AsyncTasks/WaitCooldownChange.h"

#include "AbilitySystemComponent.h"

UWaitCooldownChange* UWaitCooldownChange::WaitForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent,
                                                                const FGameplayTag& InCooldownTag)
{
	UWaitCooldownChange* WaitCooldownChange = NewObject<UWaitCooldownChange>();
	WaitCooldownChange->ASC = AbilitySystemComponent;
	WaitCooldownChange->CooldownTag = InCooldownTag;

	if(!IsValid(AbilitySystemComponent) || !InCooldownTag.IsValid())
	{
		WaitCooldownChange->EndTask();
		return nullptr;
	}
	
	AbilitySystemComponent->RegisterGameplayTagEvent(InCooldownTag,EGameplayTagEventType::NewOrRemoved).AddUObject(WaitCooldownChange,&UWaitCooldownChange::CooldownTagChanged);
	AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(WaitCooldownChange,&UWaitCooldownChange::OnActiveEffectAdded);
	return WaitCooldownChange;
}

void UWaitCooldownChange::EndTask()
{
	if(!IsValid(ASC))
	{
		return;
	}
	ASC->RegisterGameplayTagEvent(CooldownTag,EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
	ASC->OnActiveGameplayEffectAddedDelegateToSelf.RemoveAll(this);
	
	SetReadyToDestroy();
	MarkAsGarbage();
}

void UWaitCooldownChange::CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount)
{
	if(NewCount == 0)
	{
		CoolDownEnd.Broadcast(0.f);
	}
}

void UWaitCooldownChange::OnActiveEffectAdded(UAbilitySystemComponent* TargetAsc,const FGameplayEffectSpec& EffectApply, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	if(!ASC)
	{
		return;
	}
	FGameplayTagContainer AssetTags;
	EffectApply.GetAllAssetTags(AssetTags);
	
	FGameplayTagContainer GrantedTags;
	EffectApply.GetAllGrantedTags(GrantedTags);

	if (AssetTags.HasTagExact(CooldownTag) || GrantedTags.HasTagExact(CooldownTag))
	{
		FGameplayEffectQuery GameplayEffectQuery = FGameplayEffectQuery::MakeQuery_MatchAllOwningTags(CooldownTag.GetSingleTagContainer());
		TArray<float> TimesRemaining =  ASC->GetActiveEffectsDuration(GameplayEffectQuery);
		if(TimesRemaining.Num() > 0)
		{
			float HighestTime = TimesRemaining[0];
			for(int32 i = 0; i<TimesRemaining.Num();i++)
			{
				if(TimesRemaining[i] > HighestTime )
				{
					HighestTime = TimesRemaining[i];
				}
					
			}
			CoolDownStart.Broadcast(HighestTime);
		}
		
	}
}
