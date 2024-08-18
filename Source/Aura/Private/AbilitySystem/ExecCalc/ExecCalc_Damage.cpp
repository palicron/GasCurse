// CAS Tutorial JsPalacios


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
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
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChange);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);

	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitResistance,Target,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArmorPenetration,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitChange,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitDamage,Source,false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,FireResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,LightningResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArcaneResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,PhysicalResistance,Target,false);

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
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChangeDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

	TMap<FGameplayTag,FGameplayEffectAttributeCaptureDefinition> TagToCapturesDef;

	
	TagToCapturesDef.Add(FAuraGamePlayTags::Get().Attributes_Secondary_Armor,DamageStatics().ArmorDef);
	TagToCapturesDef.Add(FAuraGamePlayTags::Get().Attributes_Secondary_BlockChance,DamageStatics().BlockChanceDef);
	TagToCapturesDef.Add(FAuraGamePlayTags::Get().Attributes_Secondary_CriticalHitResistance,DamageStatics().CriticalHitResistanceDef);
	TagToCapturesDef.Add(FAuraGamePlayTags::Get().Attributes_Secondary_ArmorPenetration,DamageStatics().ArmorPenetrationDef);
	TagToCapturesDef.Add(FAuraGamePlayTags::Get().Attributes_Secondary_CriticalHitChange,DamageStatics().CriticalHitChangeDef);
		
	TagToCapturesDef.Add(FAuraGamePlayTags::Get().Attributes_Secondary_CriticalHitDamage,DamageStatics().CriticalHitDamageDef);
	TagToCapturesDef.Add(FAuraGamePlayTags::Get().Attributes_Resistance_Fire,DamageStatics().FireResistanceDef);
	TagToCapturesDef.Add(FAuraGamePlayTags::Get().Attributes_Resistance_Arcane,DamageStatics().ArcaneResistanceDef);
	TagToCapturesDef.Add(FAuraGamePlayTags::Get().Attributes_Resistance_Lightning,DamageStatics().LightningResistanceDef);
	TagToCapturesDef.Add(FAuraGamePlayTags::Get().Attributes_Resistance_Physical,DamageStatics().PhysicalResistanceDef);
	
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	int32 SourcePlayerLevel = 1;
	int32 TargetPlayerLevel = 1;
	
	if(SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	
	if(TargetAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}

	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;


	//Debuff

	DetermineDebuff(ExecutionParams, Spec, EvaluationParams,TagToCapturesDef);
	
	// Get Damage Set By Collar Magnitude
	float Damage = 0.f;
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FAuraGamePlayTags::Get().DamageTypeToResistances)
	{
		const FGameplayTag DamageType = Pair.Key;
		const FGameplayTag ResistanceType = Pair.Value;
		checkf(TagToCapturesDef.Contains(ResistanceType),TEXT("TagsTOCapture Doesnt conitain : (%s) in Exel"),*ResistanceType.ToString());
		
		const FGameplayEffectAttributeCaptureDefinition  CaptureRef = TagToCapturesDef[ResistanceType];
		float Resistance = 0;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureRef,EvaluationParams,Resistance);
		Resistance = FMath::Clamp(Resistance,0,100.f);

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key,false);

		DamageTypeValue *= (100.f - Resistance)/100.f;
		Damage += DamageTypeValue;
	}

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
	const float ArmorPenCoefficient = ArmorPenetrationCurve->Eval(SourcePlayerLevel);

	
	const FRealCurve* EffectiveArmorCurve =  CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"),FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetPlayerLevel);

	
	//ArmorPenetration Ignore a percetage of targets armor
	const float EffectiveArmor = TargetArmor *= (100.f - SourceArmorPenetration * ArmorPenCoefficient) / 100.f;
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100;

	FGameplayEffectContextHandle EffectContextHandel =  Spec.GetContext();
	UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandel,bBlocked);
	//Critical

	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChangeDef,EvaluationParams,SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance,0.f);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef,EvaluationParams,SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(SourceCriticalHitDamage,0.f);

	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef,EvaluationParams,TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max<float>(TargetCriticalHitResistance,0.f);

	const FRealCurve* CtrHitResitanceCurve =  CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("CtrHitResitance"),FString());
	const float CtrHitResitanceCoefficient = CtrHitResitanceCurve->Eval(TargetPlayerLevel);

	const float EffectiveCritHitChange = SourceCriticalHitChance - TargetCriticalHitResistance * CtrHitResitanceCoefficient;

	const bool bCritHit = FMath::RandRange(1,100) < EffectiveCritHitChange;

	Damage = bCritHit ? (Damage* 2.f) + SourceCriticalHitDamage : Damage;
	
	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandel,bCritHit);
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}


void UExecCalc_Damage::DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FGameplayEffectSpec& Spec, FAggregatorEvaluateParameters EvaluationParams
	,const TMap<FGameplayTag,FGameplayEffectAttributeCaptureDefinition>& TagToDefs ) const
{
	const FAuraGamePlayTags&  GamePlayTags = FAuraGamePlayTags::Get();
	for (const TTuple<FGameplayTag,FGameplayTag>& Pair : GamePlayTags.DamageTypeToDebuffs)
	{
		const FGameplayTag& DamageType = Pair.Key;
		const FGameplayTag& DebuffType = Pair.Value;
		const float TypeDamage = Spec.GetSetByCallerMagnitude(DamageType,false,-1.f);
		if(TypeDamage >= 0.f)
		{
			//Determine if ther was a succesfull debuff

			const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GamePlayTags.Debuff_Chance,false,-1.f);
			float TargetDebuffResistace = 0.f;
			const FGameplayTag& ResistanceTag = GamePlayTags.DamageTypeToResistances[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(TagToDefs[ResistanceTag],EvaluationParams,TargetDebuffResistace);
			TargetDebuffResistace = FMath::Max<float>(TargetDebuffResistace,0.f);

			const float EffectiveDebuffChance = SourceDebuffChance * ( 100 - TargetDebuffResistace) / 100.f;
			const bool bDebuff = FMath::RandRange(1,100) < EffectiveDebuffChance;
			if(bDebuff)
			{
				
			}
		}
	}
}
