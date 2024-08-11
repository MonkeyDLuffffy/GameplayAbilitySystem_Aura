// copyright Druid bujingyun

#pragma once

#include "CoreMinimal.h"
#include "Actor/AuraProjectile.h"
#include "AuraFireBall.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraFireBall : public AAuraProjectile
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void StartOutgoingTimeline();

	UPROPERTY(BlueprintReadOnly)
	AActor* ReturnTOActor;

	UPROPERTY(BlueprintReadOnly)
	float TravelDistance = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float ExplosionDistance = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float KnockbackMagnitude = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float DeathImpulseMagnitude = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float InnerRadius = 50.f;

	UPROPERTY(BlueprintReadOnly)
	float OuterRadius = 300.f;
	
	UPROPERTY(BlueprintReadWrite)
	FDamageEffectParams ExplosionDamageParams;
protected:
	virtual void BeginPlay() override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlapPrimitiveComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	
	virtual void OnHit() override;
};
