// CAS Tutorial JsPalacios


#include "AbilitySystem/Passive/PassiveNiagaraComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
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
	}
	else if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetOwner()))
	{
		CombatInterface->GetOnASCRegisterDelegate().AddLambda([&](UAbilitySystemComponent* ASC)
		{
			AuraASC->ActivatePassiveEffectDelegate.AddUObject(this,&UPassiveNiagaraComponent::OnPassiveActivate);
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
