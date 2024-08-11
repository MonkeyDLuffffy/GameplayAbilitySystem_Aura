// copyright Druid bujingyun


#include "AbilitySystem/Abilities/AuraFireBlast.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraFireBall.h"

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
	"<Title>火焰爆裂箭</>\n\n<Small>Level: %d</>\n<Small>MP:</><ManaCost>%.1f</>\n<Small>CD:</><Cooldown>%.1f</>\n<Default>向所有的方向发射</><Num>%d</><Default>个火焰爆裂箭,对沿途的敌人造成</><Damage>%d</><Default>点伤害，在</><Num>%.1f</><Default>码的距离返回，对沿途的敌人造成</><Damage>%d</><Default>点伤害。返回到中心时爆炸，对周围</><Num>%.1f</><Default>码范围内的敌人造成</><Damage>%d</><Default> 点火焰爆炸伤害，并能击退敌人。每次伤害都有 </><Damage>%.1f</><Default>的几率对敌人造成燃烧效果。</>\n\n"
	),
	//Value
	Level,
	-ManaCost,
	Cooldown,
	GetNumSpellsEffect(Level),
	DamageTemp,
	TravelDistance,
	DamageTemp,
	ExplosionDistance,
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
	"<Title>Next Level</>\n\n<Small>Level: %d</>\n<Small>MP:</><ManaCost>%.1f</>\n<Small>CD:</><Cooldown>%.1f</>\n<Default>向所有的方向发射</><Num>%d</><Default>个火焰爆裂箭,对沿途的敌人造成</><Damage>%d</><Default>点伤害，在</><Num>%.1f</><Default>码的距离返回，对沿途的敌人造成</><Damage>%d</><Default>点伤害。返回到中心时爆炸，对周围</><Num>%.1f</><Default>码范围内的敌人造成</><Damage>%d</><Default> 点火焰爆炸伤害。每次伤害都有 </><Damage>%.1f</><Default>的几率对敌人造成燃烧效果。</>\n\n"
	),
	//Value
	Level,
	-ManaCost,
	Cooldown,
	GetNumSpellsEffect(Level),
	DamageTemp,
	TravelDistance,
	DamageTemp,
	ExplosionDistance,
	DamageTemp,
	DebuffChance);

}

TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBalls()
{
	TArray<AAuraFireBall*> FireBalls;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FVector> Directions = UAuraAbilitySystemLibrary::EvenlyRotatedVectors(Forward, FVector::UpVector, 360.f, GetNumSpellsEffect());
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, GetNumSpellsEffect());

	for (FRotator Rot : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rot.Quaternion());
		
		AAuraFireBall* FireBall = GetWorld()->SpawnActorDeferred<AAuraFireBall>(
			FireBallClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		FireBall->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->ReturnTOActor = GetAvatarActorFromActorInfo();

		FDamageEffectParams ExplosionDamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->TravelDistance = TravelDistance;
		FireBall->ExplosionDistance = ExplosionDistance;
		FireBall->InnerRadius = RadialDamageInnerRadius;
		FireBall->OuterRadius = RadialDamageOuterRadius;
		FireBall->KnockbackMagnitude = KnockbackForceMagnitude;
		FireBall->DeathImpulseMagnitude = DeathImpulseMagnitude;
		FireBall->ExplosionDamageParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->SetOwner(GetAvatarActorFromActorInfo());
		FireBalls.Add(FireBall);
		FireBall->FinishSpawning(SpawnTransform);
	}
	return TArray<AAuraFireBall*>();
}
