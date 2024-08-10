// copyright Druid bujingyun


#include "AbilitySystem/Abilities/AuraFireBlast.h"

UAuraFireBlast::UAuraFireBlast()
{
	MaxNumSpellsEffect = 12;
}

FString UAuraFireBlast::GetDescription(int32 Level)
{
	const int32 DamageTemp = GetDamage(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
	//Title
	"<Title>火焰爆裂箭</>\n\n<Small>Level: %d</>\n<Small>MP:</><ManaCost>%.1f</>\n<Small>CD:</><Cooldown>%.1f</>\n<Default>向所有的方向发射</><Num>%d</><Default>个火焰爆裂箭,对沿途的敌人造成</><Num>%d</><Default>点伤害，在</><Num>%.1f</><Default>码的距离返回，对沿途的敌人造成</><Num>%d</><Default>点伤害。返回到中心时爆炸，对周围敌人造成</><Damage>%d</><Default> 点火焰爆炸伤害。每次伤害都有 </><Damage>%.1f</><Default>的几率对敌人造成燃烧效果。</>\n\n"
	),
	//Value
	Level,
	-ManaCost,
	Cooldown,
	GetNumSpellsEffect(),
	10,
	300.f,
	10,
	DamageTemp,
	DebuffChance);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 Level)
{
	const int32 DamageTemp = GetDamage(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
	//Title
	"<Title>火焰爆裂箭</>\n\n<Small>Level: %d</>\n<Small>MP:</><ManaCost>%.1f</>\n<Small>CD:</><Cooldown>%.1f</>\n<Default>向所有的方向发射</><Num>%d</><Default>个火焰爆裂箭,对沿途的敌人造成</><Num>%d</><Default>点伤害，在</><Num>%.1f</><Default>码的距离返回，对沿途的敌人造成</><Num>%d</><Default>点伤害。返回到中心时爆炸，对周围敌人造成</><Damage>%d</><Default> 点火焰爆炸伤害。每次伤害都有 </><Damage>%.1f</><Default>的几率对敌人造成燃烧效果。</>\n\n"
	),
	//Value
	Level,
	-ManaCost,
	Cooldown,
	GetNumSpellsEffect(Level),
	10,
	300.f,
	10,
	DamageTemp,
	DebuffChance);

}
