// CAS Tutorial JsPalacios


#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"

UDebuffNiagaraComponent::UDebuffNiagaraComponent()
{
	bAutoActivate = false;
}

void UDebuffNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetOwner());
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	
	if(ASC)
	{
		ASC->RegisterGameplayTagEvent(DebuffTag,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&UDebuffNiagaraComponent::DebuffTagChanged);
	}
	else if(CombatInterface)
	{
		CombatInterface->GetOnASCRegisterDelegate().AddWeakLambda(this,[&](UAbilitySystemComponent* InASC)
		{
			InASC->RegisterGameplayTagEvent(DebuffTag,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&UDebuffNiagaraComponent::DebuffTagChanged);
		});
	}
	if(CombatInterface)
	{
		CombatInterface->GetOnDeathDelegate().AddDynamic(this,&UDebuffNiagaraComponent::OnOwnerDeath);
	}
}

void UDebuffNiagaraComponent::DebuffTagChanged(const FGameplayTag CallBackTag, int32 NewCount)
{
	if(!IsValid(GetOwner()) || !GetOwner()->Implements<UCombatInterface>() || ICombatInterface::Execute_IsDead(GetOwner()))
	{
		return;
	}
	
	if(NewCount>0)
	{
		Activate();
	}
	else
	{
		Deactivate();
	}
}

void UDebuffNiagaraComponent::OnOwnerDeath(AActor* DeadActor)
{
	Deactivate();
}
