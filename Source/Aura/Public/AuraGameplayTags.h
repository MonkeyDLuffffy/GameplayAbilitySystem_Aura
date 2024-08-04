// copyright Druid bujingyun

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *AuraGameplayTags
 *
 *Singleton containing native Gameplay Tags
 * 
 */
struct FAuraGameplayTags
{
public:
    static const FAuraGameplayTags& Get(){return GameplayTags;}
    static void InitializeNativeGameplayTags();

	FGameplayTag Attribute_Secondary_Armor;
	FGameplayTag Attribute_Secondary_ArmorPenetration;
	FGameplayTag Attribute_Secondary_BlockChance;
	FGameplayTag Attribute_Secondary_CriticalHitChance;
	FGameplayTag Attribute_Secondary_CriticalHitDamage;
	FGameplayTag Attribute_Secondary_CriticalHitResistance;
	FGameplayTag Attribute_Secondary_HealthRegeneration;
	FGameplayTag Attribute_Secondary_ManaRegeneration;
	FGameplayTag Attribute_Secondary_MaxHealth;
	FGameplayTag Attribute_Secondary_MaxMana;

	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Vigor;

	FGameplayTag Attribute_Vital_Health;
	FGameplayTag Attribute_Vital_Mana;


	
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_Passive_1;
	FGameplayTag InputTag_Passive_2;

	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;
	
	FGameplayTag Attributes_Resistance_Fire;      //火焰抗性
	FGameplayTag Attributes_Resistance_Lightning;	//雷电抗性
	FGameplayTag Attributes_Resistance_Arcane;		//奥数抗性
	FGameplayTag Attributes_Resistance_Physical;	//物理抗性

	
	FGameplayTag Debuff_Burn;   //燃烧
	FGameplayTag Debuff_Stun;	//击晕
	FGameplayTag Debuff_Arcane;
	FGameplayTag Debuff_Physical;

	FGameplayTag Debuff_Chance;
	FGameplayTag Debuff_Damage;
	FGameplayTag Debuff_Frequency;
	FGameplayTag Debuff_Duration;
	
	FGameplayTag Attributes_Meta_IncomingXP;

	FGameplayTag Abilities_None;
	
	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;
	
	FGameplayTag Abilities_HitReact;
	
	FGameplayTag Abilities_Status_Locked;
	FGameplayTag Abilities_Status_Eligible;
	FGameplayTag Abilities_Status_Unlocked;
	FGameplayTag Abilities_Status_Equipped;

	FGameplayTag Abilities_Type_Offensive;
	FGameplayTag Abilities_Type_Passive;
	FGameplayTag Abilities_Type_None;
	
	FGameplayTag Abilities_Fire_FireBolt;
	FGameplayTag Abilities_Lightning_Electrocute;;
	
	FGameplayTag Cooldown_Fire_FireBolt;

	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_Tail;

	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	TMap<FGameplayTag, FGameplayTag> DamageTypeToResistanceMap;
	TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;
	
	
	FGameplayTag Effects_HitReact;
	

private:
	static FAuraGameplayTags GameplayTags;
};