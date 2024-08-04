// copyright Druid bujingyun


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AbilitySystem/AuraAttributeSet.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 DamageTemp = GetDamage(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
	//Title
	"<Title>火球术</>\n\n<Small>Level: %d</>\n<Small>MP:</><ManaCost>%.1f</>\n<Small>CD:</><Cooldown>%.1f</>\n<Default>发射</><Num>%d</><Default>个火球，在命中敌人或者消散的时候爆炸，造成 </><Damage>%d</><Default> 点火焰伤害，该伤害有一定几率可以燃烧。</>\n\n"
	),
	//Value
	Level,
	-ManaCost,
	Cooldown,
	FMath::Min(Level, NumProjectiles),
	DamageTemp);

}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 DamageTemp = GetDamage(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
	//Title
	"<Title>Next Level</>\n\n<Small>Level: %d</>\n<Small>MP:</><ManaCost>%.1f</>\n<Small>CD:</><Cooldown>%.1f</>\n<Default>发射</><Num>%d</><Default>个火球，在命中敌人或者消散的时候爆炸，造成 </><Damage>%d</><Default> 点火焰伤害，该伤害有一定几率可以燃烧。</>\n\n"
	),
	//Value
	Level,
	-ManaCost,
	Cooldown,
	FMath::Min(Level, NumProjectiles),
	DamageTemp);
}

float UAuraFireBolt::GetManaCost(float InLevel) const
{
	float ManaCost = 0.f;
	if(const UGameplayEffect* CostEffect = GetCostGameplayEffect())
	{
		for (FGameplayModifierInfo Mod : CostEffect->Modifiers)
		{
			if(Mod.Attribute == UAuraAttributeSet::GetManaAttribute())
			{
				Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, ManaCost);
				break;
			}
		}
	}
	return ManaCost;
}

float UAuraFireBolt::GetCoolDown(float InLevel)
{
	float Cooldown = 0.f;
	if(const UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect())
	{
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, Cooldown);
	}
	return Cooldown;
}
