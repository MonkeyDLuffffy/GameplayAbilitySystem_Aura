// copyright Druid bujingyun


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 DamageTemp = GetDamage(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
	//Title
	"<Title>火焰箭</>\n\n<Small>Level: %d</>\n<Small>MP:</><ManaCost>%.1f</>\n<Small>CD:</><Cooldown>%.1f</>\n<Default>发射</><Num>%d</><Default>个火球，在命中敌人或者消散的时候爆炸，造成 </><Damage>%d</><Default> 点火焰伤害，该伤害有 </><Damage>%.1f</><Default>的几率可以燃烧。</>\n\n"
	),
	//Value
	Level,
	-ManaCost,
	Cooldown,
	GetNumSpellsEffect(),
	DamageTemp,
	DebuffChance);
	
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 DamageTemp = GetDamage(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
	//Title
	"<Title>火焰箭</>\n\n<Small>Level: %d</>\n<Small>MP:</><ManaCost>%.1f</>\n<Small>CD:</><Cooldown>%.1f</>\n<Default>发射</><Num>%d</><Default>个火球，在命中敌人或者消散的时候爆炸，造成 </><Damage>%d</><Default> 点火焰伤害，该伤害有 </><Damage>%.1f</><Default>的几率可以燃烧。</>\n\n"
	),
	//Value
	Level,
	-ManaCost,
	Cooldown,
	GetNumSpellsEffect(Level),
	DamageTemp,
	DebuffChance);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
	bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsSever = GetAvatarActorFromActorInfo()->HasAuthority();
	if(!bIsSever) return;
	
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(),SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if(bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}
	const FVector Forward = Rotation.Vector();
	const int32 NumProjectiles = GetNumSpellsEffect();
	//const int32 NumProjectiles = FMath::Min(GetAbilityLevel(), MaxNumProjectiles);
	TArray<FVector> Directions = UAuraAbilitySystemLibrary::EvenlyRotatedVectors(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);

	for (const FRotator& Rot : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());
		//Set the Projectile Rotation
	
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
				ProjectileClass,SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(GetOwningActorFromActorInfo()),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		if(HomingTarget && HomingTarget->Implements<UCombatInterface>())
		{
			Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
		}
		else
		{
			Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
			Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
			Projectile->ProjectileMovement->HomingTargetComponent = Projectile->HomingTargetSceneComponent;
			
		}
		Projectile->ProjectileMovement->bIsHomingProjectile = bLaunchHomingProjectiles;
		Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::FRandRange(HomingAccelerationMin, HomingAccelerationMax);
		Projectile->FinishSpawning(SpawnTransform);
	}
}
