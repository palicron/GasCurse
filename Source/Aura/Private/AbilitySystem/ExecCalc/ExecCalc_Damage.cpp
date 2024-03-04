// CAS Tutorial JsPalacios


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGamePlayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct AuraDamageStatics
{

	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArmorPenetration,Source,false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatic;
	return DStatic;
}
UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const ICombatInterface* SourceCombatI = Cast<ICombatInterface>(SourceAvatar);
	const ICombatInterface* TargetCombatI = Cast<ICombatInterface>(TargetAvatar);
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	// Get Damage Set By Collar Magnitude
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGamePlayTags::Get().Damage);

	//Capture BlockChange on Taget, and determine if there was a succesful Block
	
	float TargetBlockChance = 0.f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef,EvaluationParams,TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance,0.f);

	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluationParams,TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor,0.f);

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef,EvaluationParams,SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration,0.f);

	//If block, halve damage
	const bool bBlocked = FMath::RandRange(1,100) < TargetBlockChance;
	Damage = bBlocked ? Damage * 0.5f : Damage;

	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenetrationCurve =  CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"),FString());
	const float ArmorPenCoefficient = ArmorPenetrationCurve->Eval(SourceCombatI->GetPlayerLevel());

	
	const FRealCurve* EffectiveArmorCurve =  CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"),FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatI->GetPlayerLevel());
	
	//ArmorPenetration Ignore a percetage of targets armor
	const float EffectiveArmor = TargetArmor *= (100.f - SourceArmorPenetration * ArmorPenCoefficient) / 100.f;
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100;
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
