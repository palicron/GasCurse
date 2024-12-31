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

FDamageEffectParams UAuraDamageGameplayAbility::MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor, FVector InRadialDamageOrigin,bool bOverrideKnockBackDirection, FVector InKnockBackDirectionDirection,
	bool bOverrideDeathImpulse, FVector DeathImpulseOverride, bool bOverridePitch, float PitchOverRide) const 
{
	FDamageEffectParams Params;
	Params.WorldContextObject = GetAvatarActorFromActorInfo();
	Params.DamageGameplayEffectClass = DamageEffectClass;
	Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	Params.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	Params.BaseDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	Params.AbilityLevel = GetAbilityLevel();
	Params.DamageType = DamageType;
	Params.DebuffDamage = DebuffDamage;
	Params.DebuffChance = DebuffChance;
	Params.DebuffDuration = DebuffDuration;
	Params.DebuffFrequency = DebuffFrequency;
	Params.DeathImpulseMagnitude = DeathImpulseMagnitude;
	Params.KnockBackForceMagnitude = KnockBackForceMagnitude;
	Params.KnockBackChance = KnockBackChance;

	FRotator ToTarget;
	if(IsValid(TargetActor))
	{
		 ToTarget = (TargetActor->GetActorLocation() - GetAvatarActorFromActorInfo()->GetActorLocation()).Rotation();

		ToTarget.Pitch = 45.f;
		if (bOverridePitch)
		{
			ToTarget.Pitch = PitchOverRide;
		}

		Params.DeathImpulse = ToTarget.Vector().GetSafeNormal() * DeathImpulseMagnitude;
	}

	if (bOverrideKnockBackDirection)
	{
		InKnockBackDirectionDirection.Normalize();
		
		Params.KnockBackForce = InKnockBackDirectionDirection * KnockBackForceMagnitude;
		if (bOverridePitch)
		{
			FRotator KnockBackRotation = InKnockBackDirectionDirection.Rotation();
			KnockBackRotation.Pitch = PitchOverRide;
			Params.KnockBackForce = KnockBackRotation.Vector() * KnockBackForceMagnitude;
		}
	}
	else
	{
		if(FMath::RandRange(1,100) <= KnockBackChance)
		{
			Params.KnockBackForce = ToTarget.Vector().GetSafeNormal() * KnockBackForceMagnitude;
		}
	}
	if (bOverrideDeathImpulse)
	{
		DeathImpulseOverride.Normalize();
		Params.DeathImpulse = DeathImpulseOverride * DeathImpulseMagnitude;

		if (bOverridePitch)
		{
			FRotator KnockBackRotation = DeathImpulseOverride.Rotation();
			KnockBackRotation.Pitch = PitchOverRide;
			Params.DeathImpulse = KnockBackRotation.Vector() * DeathImpulseMagnitude;
		}
	}
	else
	{
		if(FMath::RandRange(1,100) <= KnockBackChance)
		{
			Params.DeathImpulse = ToTarget.Vector().GetSafeNormal() * KnockBackForceMagnitude;
		}
	}
	
	
	if (bIsRadialDamage)
	{
		Params.bIsRadialDamage = bIsRadialDamage;
		Params.RadialDamageInnerRadius = RadialDamageInnerRadius;
		Params.RadialDamageOuterRadius = RadialDamageOuterRadius;
		Params.RadialDamageOrigin = InRadialDamageOrigin;
	}
	
	return Params;
}

float UAuraDamageGameplayAbility::GetDamageAtLevel() const
{
	return Damage.GetValueAtLevel(GetAbilityLevel());
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
