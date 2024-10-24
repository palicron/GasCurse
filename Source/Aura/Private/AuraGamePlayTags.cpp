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

	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Passive_1"), FString("Passive 1"));

	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Passive_2"), FString("Passive 2"));
	
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
	 * Meta
	 */

	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Meta.IncomingXP"), FString("IncomingXP"));
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

	GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.None"), FString("Tag To None"));
	
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Attack"), FString("Tag To Melee Attack"));

	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.HitReact"), FString("Tag To Abilities HitReact"));

	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Eligible"), FString("Tag To Status Eligible"));

	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Locked"), FString("Tag To Status Locked"));
	
	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.UnLocked"), FString("Tag To Status UnLocked"));
	
	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Equipped"), FString("Tag To Status Equipped"));
	
	GameplayTags.Abilities_Status_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Offensive"), FString("Tag To Status Offensive"));

	GameplayTags.Abilities_Status_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Passive"), FString("Tag To Status Passive"));
	
	GameplayTags.Abilities_Status_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.None"), FString("Tag To Status None"));
	
	/*
	 * Sockets
	 */
	
	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.Weapon"), FString("Weapon"));

	GameplayTags.CombatSocket_RightHand= UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.RightHand"), FString("RightHand"));

	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.LeftHand"), FString("LeftHand"));

	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.Tail"), FString("Tail"));
	/*
	* Montage
	*/

	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.1"), FString("Attack 1"));

	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.2"), FString("Attack 2"));

	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.3"), FString("Attack 3"));

	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.4"), FString("Attack 4"));

	GameplayTags.Montage_Attack_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.5"), FString("Attack 5"));

	
	GameplayTags.Abilities_Summon= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Summon"), FString("Summon"));
	
	GameplayTags.Abilities_Fire_FireBolt= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Fire.FireBolt"),FString("FireBoldt"));

	GameplayTags.Cooldown_Fire_FireBolt= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Fire.FireBolt"),FString("Cooldown FireBolt"));

	GameplayTags.Abilities_Lightning_Electrocute= UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Lightning.Electrocute"),FString("Electrocute"));

//Debuff

	GameplayTags.Debuff_Burn= UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Debuff.Burn"),FString("Burn Debuff"));

	GameplayTags.Debuff_Stun= UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Debuff.Stun"),FString("Stun Debuff"));

	GameplayTags.Debuff_Arcane= UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Debuff.Arcane"),FString("Arcane Debuff"));

	GameplayTags.Debuff_Physical= UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Debuff.Physical"),FString("Physical Debuff"));

	GameplayTags.DamageTypeToDebuffs.Add(GameplayTags.Damage_Arcane,GameplayTags.Debuff_Arcane);
	GameplayTags.DamageTypeToDebuffs.Add(GameplayTags.Damage_Fire,GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypeToDebuffs.Add(GameplayTags.Damage_Lightning,GameplayTags.Debuff_Stun);
	GameplayTags.DamageTypeToDebuffs.Add(GameplayTags.Damage_Physical,GameplayTags.Debuff_Physical);

	GameplayTags.Debuff_Chance= UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Debuff.Chance"),FString("Chance Debuff"));

	GameplayTags.Debuff_Damage= UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Debuff.Damage"),FString("Damage Debuff"));

	GameplayTags.Debuff_Frequency= UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Debuff.Frequency"),FString("Frequency Debuff"));

	GameplayTags.Debuff_Duration= UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Debuff.Duration"),FString("Duration Debuff"));

	/**
	 *Player Block tags
	 **/

	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Player.Block.CursorTrace"),FString("Block CursorTrace"));

	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Player.Block.InputHeld"),FString("Block InputHeld"));

	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Player.Block.InputPressed"),FString("Block InputPressed"));

	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Player.Block.InputReleased"),FString("Block InputReleased"));
	
/**
 * Passive
 */

	GameplayTags.Abilities_Passive_LifeSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Passive.LifeSiphon"),FString("Passive LifeSiphon"));

	GameplayTags.Abilities_Passive_ManaSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Passive.ManaSiphon"),FString("Passive.ManaSiphon"));

	GameplayTags.Abilities_Passive_HaloOfProtection = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Passive.HaloOfProtection"),FString("HaloOfProtection"));
}

