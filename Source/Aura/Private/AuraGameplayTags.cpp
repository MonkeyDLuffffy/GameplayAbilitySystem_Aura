// copyright Druid bujingyun


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Secondary Attributes
	 */
	GameplayTags.Attribute_Secondary_Armor=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("Reduces damage taken, improves Block Chance"));
	GameplayTags.Attribute_Secondary_ArmorPenetration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"),FString("护甲穿透:忽略敌人护甲的百分比，增加爆击几率"));
	GameplayTags.Attribute_Secondary_BlockChance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),FString("抵抗几率：有机会将来袭伤害减半"));
	GameplayTags.Attribute_Secondary_CriticalHitChance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"),FString("暴击率：几率双倍伤害加致命一击加成"));
	GameplayTags.Attribute_Secondary_CriticalHitDamage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"),FString("爆伤"));
	GameplayTags.Attribute_Secondary_CriticalHitResistance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"),FString("暴击抵抗：减少攻击敌人的暴击几率"));
	GameplayTags.Attribute_Secondary_HealthRegeneration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),FString("生命回复：每秒回复的生命值"));
	GameplayTags.Attribute_Secondary_ManaRegeneration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),FString("法力回复：每秒回复的法力值"));
	GameplayTags.Attribute_Secondary_MaxHealth=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),FString("最大生命值"));
	GameplayTags.Attribute_Secondary_MaxMana=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),FString("最大魔法值"));

	/*
	* Primary Attributes
	*/
	GameplayTags.Attribute_Primary_Intelligence=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"),FString("智力"));
	GameplayTags.Attribute_Primary_Resilience=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"),FString("韧性"));
	GameplayTags.Attribute_Primary_Strength=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"),FString("力量"));
	GameplayTags.Attribute_Primary_Vigor=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"),FString("活力"));

	/*
	* Vital Attributes
	*/
	GameplayTags.Attribute_Vital_Health=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"),FString("生命"));
	GameplayTags.Attribute_Vital_Mana=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"),FString("魔法"));

	/*
	* Input Action
	*/
	GameplayTags.InputTag_LMB=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"),FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"),FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_1=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"),FString("Input Tag for 1 key"));
	GameplayTags.InputTag_2=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"),FString("Input Tag for 2 key"));
	GameplayTags.InputTag_3=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"),FString("Input Tag for 3 key"));
	GameplayTags.InputTag_4=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"),FString("Input Tag for 4 key"));
	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.1"),FString("Input Passive_1 Ability"));
	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.2"),FString("Input Passive_2 Ability"));
	
	/*
	 * DamageTypes
	 */
	GameplayTags.Damage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"),FString("Damage"));
	GameplayTags.Damage_Fire=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"),FString("Fire Damage Type"));
	GameplayTags.Damage_Lightning=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"),FString("Lightning Damage Type"));
	GameplayTags.Damage_Arcane=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Arcane"),FString("Arcane Damage Type"));
	GameplayTags.Damage_Physical=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"),FString("Physical Damage Type"));

	/*
	 *Resistances 
	 */
	GameplayTags.Attributes_Resistance_Fire=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"), FString("Fire Resistance"));
	GameplayTags.Attributes_Resistance_Lightning=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"), FString("Lightning Resistance"));
	GameplayTags.Attributes_Resistance_Arcane=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Arcane"), FString("Arcane Resistance"));
	GameplayTags.Attributes_Resistance_Physical=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"), FString("Physical Resistance"));

	/*
	 * Debuff
	 */
	GameplayTags.Debuff_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Physical"), FString("Physical Debuff for Physical damage"));
	GameplayTags.Debuff_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Arcane"), FString("Arcane Debuff for Arcane damage"));
	GameplayTags.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Burn"), FString("Burn Debuff for fire damage"));
	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Stun"), FString("Stun Debuff for Lightning damage"));

	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Chance"), FString(" Debuff chance"));
	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Damage"), FString(" Debuff  damage"));
	GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Frequency"), FString("Debuff Frequency"));
	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Duration"), FString("Debuff Duration"));
	
	/*
	 * Map of Damage Types to Resistances
	 */
	GameplayTags.DamageTypeToResistanceMap.Add(GameplayTags.Damage_Fire,GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypeToResistanceMap.Add(GameplayTags.Damage_Lightning,GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypeToResistanceMap.Add(GameplayTags.Damage_Arcane,GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypeToResistanceMap.Add(GameplayTags.Damage_Physical,GameplayTags.Attributes_Resistance_Physical);

	/*
	* Map of Damage Types to Debuff
	*/
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Arcane,GameplayTags.Debuff_Arcane);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Physical,GameplayTags.Debuff_Physical);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Fire,GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Lightning,GameplayTags.Debuff_Stun);
	
	GameplayTags.Effects_HitReact=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"),FString("Tag Granted when Hit Reacting"));

	/*
	 * Abilities
	 */
	GameplayTags.Abilities_Attack=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"),FString("Attack Ability Tag"));
	GameplayTags.Abilities_Summon=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Summon"),FString("Summon Ability Tag"));
	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"),FString("FireBolt Ability Tag"));
	GameplayTags.Abilities_Lightning_Electrocute = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Lightning.Electrocute"),FString("Electrocute Ability Tag"));
	
	
	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.HitReact"),FString("Hit React Ability"));
	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Eligible"),FString("Ability Eligible status"));
	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Equipped"),FString("Ability Equipped status"));
	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Locked"),FString("Ability Locked status"));
	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Unlocked"),FString("Ability Unlocked status"));

	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Offensive"),FString("Offensive Type Ability"));
	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Passive"),FString("Passive Type Ability"));
	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.None"),FString("None Type Ability"));

	GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.None"),FString("No Ability - like the nullptr for Ability Tags"));
	
	/*
	 * Cooldown
	 */
	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"),FString("FireBolt Ability Cooldown Tag"));
	
	/*
	* Combat Sockets
	*/
	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"),FString("Socket Weapon Tag"));
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftHand"),FString("Socket Left Hand Tag"));
	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightHand"),FString("Socket Right Hand Tag"));
	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tail"),FString("Socket Tail Tag"));

	
	/*
	* Montage Tags
	*/
	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.1"),FString("Attack 1"));
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.2"),FString("Attack 2"));
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.3"),FString("Attack 3"));
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.4"),FString("Attack 4"));

	/*
	 * Meta Attributes
	 */
	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingXP"),FString("Incoming XP Meta Attribute"));
}
