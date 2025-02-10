// CAS Tutorial JsPalacios


#include "AbilitySystem/Passive/PassiveNiagaraComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGamePlayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Interaction/CombatInterface.h"

UPassiveNiagaraComponent::UPassiveNiagaraComponent()
{
	bAutoActivate = false;
}

void UPassiveNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();
	if(UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner())))
	{
		AuraASC->ActivatePassiveEffectDelegate.AddUObject(this,&UPassiveNiagaraComponent::OnPassiveActivate);
		if (const bool bStartUpAbilitiesGiven = AuraASC->bStartupAbilitiesGiven)
		{
			if (AuraASC->GetStatusFromAbilityTag(PassiveSpellTag) == FAuraGamePlayTags::Get().Abilities_Status_Equipped)
			{
				Activate();
			}
		}
	}
	else if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetOwner()))
	{
		CombatInterface->GetOnASCRegisterDelegate().AddLambda([&](UAbilitySystemComponent* ASC)
		{
			if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(ASC))
			{
				AuraASC->ActivatePassiveEffectDelegate.AddUObject(this, &UPassiveNiagaraComponent::OnPassiveActivate);

				if (const bool bStartUpAbilitiesGiven = AuraASC->bStartupAbilitiesGiven)
				{
					if (AuraASC->GetStatusFromAbilityTag(PassiveSpellTag) == FAuraGamePlayTags::Get().
						Abilities_Status_Equipped)
					{
						Activate();
					}
				}
			}
		});
	}
}

void UPassiveNiagaraComponent::OnPassiveActivate(const FGameplayTag& AbilityTag, const bool bIsActiveRef)
{
	if (!AbilityTag.MatchesTagExact(PassiveSpellTag))
	{
		return;
	}

	if (bIsActiveRef && !IsActive())
	{
		Activate();
		return;
	}

	Deactivate();
}
