// copyright Druid bujingyun


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

FString UAuraGameplayAbility::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>%s, </><Level>%d</>"), L"Default Ability Name - LoremIpsum LoremIpsum LoremIpsum LoremIpsum", Level);
}

FString UAuraGameplayAbility::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>下一级：</><Level>%d</> \n<Default>造成更多的伤害</>"), Level);
}

FString UAuraGameplayAbility::GetLockLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>技能%d级解锁</>"), Level);
}