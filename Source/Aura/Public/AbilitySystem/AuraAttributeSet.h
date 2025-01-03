// CAS Tutorial JsPalacios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

template<class T>
using TAttributeFuncPtr = T(*)();

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayEffectContextHandle EffectContextHandle;
	
	FEffectProperties(){}
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;


	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;

};
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// in the curse the to this TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr FunctionPointer;
	TMap<FGameplayTag,TAttributeFuncPtr<FGameplayAttribute>> TagsToAttribute;
	
//----------------------------------------------------------------------------------------------------------------------
	
	/**Vital Attributes*/
	UPROPERTY(ReplicatedUsing = OnRep_Health, EditAnywhere,BlueprintReadWrite,Category="Attribute Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health)
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UPROPERTY(ReplicatedUsing = OnRep_Mana, EditAnywhere,BlueprintReadWrite,Category="Attribute Mana")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana)
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);

	/*
	 * Meta Attributes
	 */
	
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attribute")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,IncomingDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attribute")
	FGameplayAttributeData IncomingXP;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,IncomingXP)
	
	/*Primary Attributes**/

	UPROPERTY(ReplicatedUsing = OnRep_Strength, EditAnywhere,BlueprintReadWrite,Category="Primary Attribute")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Strength)
	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UPROPERTY(ReplicatedUsing = OnRep_Intelligence, EditAnywhere,BlueprintReadWrite,Category="Primary Attribute")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Intelligence)
	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);

	UPROPERTY(ReplicatedUsing = OnRep_Resilience, EditAnywhere,BlueprintReadWrite,Category="Primary Attribute")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resilience)
	UFUNCTION()
	virtual void OnRep_Resilience(const FGameplayAttributeData& OldResilience);

	UPROPERTY(ReplicatedUsing = OnRep_Vigor, EditAnywhere,BlueprintReadWrite,Category="Primary Attribute")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Vigor)
	UFUNCTION()
	virtual void OnRep_Vigor(const FGameplayAttributeData& OldVigor);

	/*Secondary Attributes*/

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, EditAnywhere,BlueprintReadWrite,Category="Attribute Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth)
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	
	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, EditAnywhere,BlueprintReadWrite,Category="Attribute Mana")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana)
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);

	UPROPERTY(ReplicatedUsing = OnRep_Armor, EditAnywhere,BlueprintReadWrite,Category="Secondary")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Armor)
	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldArmor);

	UPROPERTY(ReplicatedUsing = OnRep_ArmorPenetration, EditAnywhere,BlueprintReadWrite,Category="Secondary")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ArmorPenetration)
	UFUNCTION()
	virtual void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration);

	UPROPERTY(ReplicatedUsing = OnRep_BlockChance, EditAnywhere,BlueprintReadWrite,Category="Secondary")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,BlockChance)
	UFUNCTION()
	virtual void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance);

	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitChange, EditAnywhere,BlueprintReadWrite,Category="Secondary")
	FGameplayAttributeData CriticalHitChange;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitChange)
	UFUNCTION()
	virtual void OnRep_CriticalHitChange(const FGameplayAttributeData& OldCriticalHitChange);

	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitDamage, EditAnywhere,BlueprintReadWrite,Category="Secondary")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitDamage)
	UFUNCTION()
	virtual void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage);

	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitResistance, EditAnywhere,BlueprintReadWrite,Category="Secondary")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitResistance)
	UFUNCTION()
	virtual void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance);

	UPROPERTY(ReplicatedUsing = OnRep_HealthRegeneration, EditAnywhere,BlueprintReadWrite,Category="Secondary")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,HealthRegeneration)
	UFUNCTION()
	virtual void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration);

	UPROPERTY(ReplicatedUsing = OnRep_ManaRegeneration, EditAnywhere,BlueprintReadWrite,Category="Secondary")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ManaRegeneration)
	UFUNCTION()
	virtual void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration);
	/**
	 * Resistance
	 */

	UPROPERTY(ReplicatedUsing = OnRep_FireResistance, EditAnywhere,BlueprintReadWrite,Category="Resistance")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,FireResistance)
	UFUNCTION()
	virtual void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance);

	UPROPERTY(ReplicatedUsing = OnRep_LightningResistance, EditAnywhere,BlueprintReadWrite,Category="Resistance")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,LightningResistance)
	UFUNCTION()
	virtual void OnRep_LightningResistance(const FGameplayAttributeData& OldFLightningResistance);
	
	UPROPERTY(ReplicatedUsing = OnRep_ArcaneResistance, EditAnywhere,BlueprintReadWrite,Category="Resistance")
	FGameplayAttributeData ArcaneResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ArcaneResistance)
	UFUNCTION()
	virtual void OnRep_ArcaneResistance(const FGameplayAttributeData& OldFArcaneResistance);

	UPROPERTY(ReplicatedUsing = OnRep_PhysicalResistance, EditAnywhere,BlueprintReadWrite,Category="Resistance")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,PhysicalResistance)
	UFUNCTION()
	virtual void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance);
	
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	void ShowFloatingText(FEffectProperties Props, float LocalIncomingDamage, bool bBlockedHit, bool bCriticalHit) const;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

private:

	void HandleIncomingDamage(const FEffectProperties& Props);
	void HandleIncomingXP(const FEffectProperties& Props);
	void HandleDebuff(const FEffectProperties& Props);
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& Props) const;
	void SendXPEvent(const FEffectProperties& Props);

	bool bTopOffHealth = false;
	bool bTopOffMana = false;
	
};



