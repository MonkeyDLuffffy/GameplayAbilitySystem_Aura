// copyright Druid bujingyun

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
struct FActiveGameplayEffectHandle;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AAuraEffectActor();


protected:

	virtual void BeginPlay() override;
	

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	bool bDestroyOnEffectRemoval=false;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target,TSubclassOf<UGameplayEffect>GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor *TargetActor);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Instant")
	EEffectApplicationPolicy InstantEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Instant")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Duration")
	EEffectApplicationPolicy DurationEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Duration")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Infinite")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Infinite")
	EEffectRemovalPolicy InfiniteEffectARemovalPolicy=EEffectRemovalPolicy::DoNotRemove;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Infinite")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandleMap;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	float Actorlevel=1.0f;
};
