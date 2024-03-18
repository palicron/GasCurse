// CAS Tutorial JsPalacios


#include "AuraGamePlayTags.h"
#include "GameplayTagsManager.h"

FAuraGamePlayTags FAuraGamePlayTags::GameplayTags;

void FAuraGamePlayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"), FString("Strength"));

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"), FString("Intelligence"));

	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"), FString("Resilience"));

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"), FString("Vigor"));
	
	
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improve Block Chance"));

	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"), FString("Max health of a Character"));

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"), FString("Max Mana of a Character"));

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"), FString("ArmorPenetration"));

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"), FString("BlockChance"));
	
	GameplayTags.Attributes_Secondary_CriticalHitChange = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChange"), FString("CriticalHitChange"));
	
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"), FString("CriticalHitDamage"));
	
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"), FString("CriticalHitResistance"));

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"), FString("HealthRegeneration"));

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"), FString("ManaRegeneration"));

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.LMB"), FString("Input tag  fot left mouse button"));

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.RMB"), FString("Input tag  fot Right mouse button"));

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.1"), FString("Input tag  fot 1 button"));

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.2"), FString("Input tag  fot 2 button"));

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.3"), FString("Input tag  fot 3 button"));
	
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.4"), FString("Input tag  fot 4 button"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage"), FString("Damage"));

	/*
	 * Damage Types
	 */
	
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Fire"), FString("Fire Damage Type"));

	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Lightning"), FString("Lightning  Damage Type"));

	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Arcane"), FString("Arcane Damage Type"));

	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Physical"), FString("Physical Damage Type"));
	
	/*
	* Resistances 
	*/

	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resistance.Fire"), FString("Resistance to Fire"));

	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resistance.Arcane"), FString("Resistance to Arcane"));

	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resistance.Lightning"), FString("Resistance to Lightning"));

	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resistance.Physical"), FString("Resistance to Physical"));

	/*
	 * Map of Damage types to Resistances
	 */

	GameplayTags.DamageTypeToResistances.Add(GameplayTags.Damage_Arcane,GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypeToResistances.Add(GameplayTags.Damage_Fire,GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypeToResistances.Add(GameplayTags.Damage_Lightning,GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypeToResistances.Add(GameplayTags.Damage_Physical,GameplayTags.Attributes_Resistance_Physical);
	
	/*
	 * Effects
	 */
	
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Effects.HitReact"), FString("Tag granted when hit Reacting"));

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Attack"), FString("Tag To Melee Attack"));

}
