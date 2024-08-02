// copyright Druid bujingyun


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/EnemyInterface.h"


void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{

	const FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);

	/*将伤害分配到SpecHandle中*/
	for (TTuple<FGameplayTag, FScalableFloat>& Pair : DamageTypeMap)
	{
		const float ScaleDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, Pair.Key, ScaleDamage);
	}

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(),UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));

}

FTaggedMontage UAuraDamageGameplayAbility::GetRandomTaggedMontageFromArray(
	const TArray<FTaggedMontage>& TaggedMontages) const
{
	if(TaggedMontages.Num()>0)
	{
		const int32 Selection = FMath::RandRange(0,TaggedMontages.Num() - 1);
		return  TaggedMontages[Selection];
	}
	return FTaggedMontage();
}

float UAuraDamageGameplayAbility::GetDamageByDamageType(float InLevel, const FGameplayTag& DamageType)const 
{
	checkf(DamageTypeMap.Contains(DamageType),TEXT("GameplayAbility [%s] does not contain DamageType [%s]"), *GetNameSafe(this), *DamageType.ToString());
	return  DamageTypeMap[DamageType].GetValueAtLevel(InLevel);
}

void UAuraDamageGameplayAbility::UpdateAttackFaceTarget()
{
	if(AActor* EnemyActor= IEnemyInterface::Execute_GetCombatTarget(GetAvatarActorFromActorInfo()))
	{
		FVector TargetLocation = EnemyActor->GetActorLocation();
		ICombatInterface::Execute_UpdateFacingTarget(GetAvatarActorFromActorInfo(), TargetLocation);
	}
}
