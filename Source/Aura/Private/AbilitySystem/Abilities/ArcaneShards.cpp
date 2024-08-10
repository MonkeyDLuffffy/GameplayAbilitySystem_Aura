// copyright Druid bujingyun


#include "AbilitySystem/Abilities/ArcaneShards.h"

FString UArcaneShards::GetDescription(int32 Level)
{
	const int32 DamageTemp = GetDamage(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
	//Title
	"<Title>奥术地刺</>\n\n<Small>Level: %d</>\n<Small>MP:</><ManaCost>%.1f</>\n<Small>CD:</><Cooldown>%.1f</>\n<Default>从地上生长</><Num>%d</><Default>个奥术地刺，造成 </><Damage>%d</><Default> 点奥术伤害，该伤害有 </><Damage>%.1f</><Default>的几率可以击退敌人。</>\n\n"
	),
	//Value
	Level,
	-ManaCost,
	Cooldown,
	GetNumSpellsEffect(),
	DamageTemp,
	KnockbackChance);
}

FString UArcaneShards::GetNextLevelDescription(int32 Level)
{
	const int32 DamageTemp = GetDamage(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
	//Title
	"<Title>奥术地刺</>\n\n<Small>Level: %d</>\n<Small>MP:</><ManaCost>%.1f</>\n<Small>CD:</><Cooldown>%.1f</>\n<Default>从地上生长</><Num>%d</><Default>个奥术地刺，造成 </><Damage>%d</><Default> 点奥术伤害，该伤害有 </><Damage>%.1f</><Default>的几率可以击退敌人。</>\n\n"
	),
	//Value
	Level,
	-ManaCost,
	Cooldown,
	GetNumSpellsEffect(Level),
	DamageTemp,
	KnockbackChance);
}

