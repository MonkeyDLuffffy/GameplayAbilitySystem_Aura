// copyright Druid bujingyun


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	const float DamageTemp = GetDamage(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
	//Title
	"<Title>闪电链</>\n\n<Small>Level:%d</>\n<Small>CD:</><Cooldown>%.1f</>\n\n<Default>发射一条闪电链，命中第一个敌人后，最多弹射</><Num>%d</><Default>个敌人。每秒造成</><Num>%.1f</><Default>次的闪电伤害，伤害值为</><Damage>%.1f</><Default>，最多持续</><Time>%.1f</><Default>秒，并击晕敌人。每次伤害消耗</><ManaCost>%.1f</><Default>点MP。</>\n\n"
	),
	//Value
	Level,
	Cooldown,
	GetNumSpellsEffect(),
	1/DamageAndCostDeltaTime,
	DamageTemp,
	MaxSpellDurationTime,
	-ManaCost);
}

FString UElectrocute::GetNextLevelDescription(int32 Level)
{
	const float DamageTemp = GetDamage(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
	//Title
	"<Title>闪电链</>\n\n<Small>Level:%d</>\n<Small>CD:</><Cooldown>%.1f</>\n\n<Default>发射一条闪电链，最多弹射</><Num>%d</><Default>个敌人。每秒造成</><Num>%d</><Default>次的闪电伤害，伤害值为</><Damage>%.1f</><Default>，最多持续</><Time>%.1f</><Default>秒，并击晕敌人。每次伤害消耗</><ManaCost>%.1f</><Default>点MP。</>\n\n"
	),
	//Value
	Level,
	Cooldown,
	GetNumSpellsEffect(Level),
	3,
	DamageTemp,
	10.f,
	-ManaCost);
}
