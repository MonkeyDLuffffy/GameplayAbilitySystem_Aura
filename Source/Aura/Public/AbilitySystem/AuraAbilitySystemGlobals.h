// copyright Druid bujingyun

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AuraAbilitySystemGlobals.generated.h"

/**
 * 在自定义的全局技能系统类中，将FGameplayEffectContext替换为自定义的FAuraGameplayEffectContext
 * 在Config\DefaultGame.ini文件中将全局技能系统类添加到游戏配置中
 * [/Script/GameplayAbilities.AbilitySystemGlobals]
 + AbilitySystemGlobalsClassName="/Script/Aura.AuraAbilitySystemGlobals"
 */
UCLASS()
class AURA_API UAuraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
public:
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
