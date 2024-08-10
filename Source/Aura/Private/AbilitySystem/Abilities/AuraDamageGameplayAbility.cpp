// CAS Tutorial JsPalacios


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	if(IsValid(DamageEffectClass))
	{
		FGameplayEffectSpecHandle DamageSpecHandel = MakeOutgoingGameplayEffectSpec(DamageEffectClass,1.f);
	
		const float DamageMagnitude = Damage.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandel,DamageType,DamageMagnitude);
		
		GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandel.Data.Get(),UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
	}
	
}

FTaggedMontage UAuraDamageGameplayAbility::GetRandomTagMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const
{
	if(TaggedMontages.Num()>0)
	{
		const int32 selection =FMath::RandRange(0,TaggedMontages.Num()-1);
		return TaggedMontages[selection];
	}

	return FTaggedMontage();
}
