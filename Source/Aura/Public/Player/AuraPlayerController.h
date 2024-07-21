// copyright Druid bujingyun

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"
struct FGameplayTag;
class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UAuraAbilitySystemComponent;
class USplineComponent;
class UDamageTextComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	AAuraPlayerController();
	FVector GetMouseCursorLocation() const;
	bool  FindMouseResultHit(FHitResult & HitResult) const;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter);
protected:

	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ShiftAction;

	void Move(const FInputActionValue &InputActionValue) ;
	void ShiftPressed(){ bShiftKeyDown = true; }
	void ShiftReleased(){ bShiftKeyDown = false; }
	bool bShiftKeyDown = false;

	void CursorTrace();

	

	IEnemyInterface *LastActor;
	IEnemyInterface *ThisActor;
	FHitResult CursorHit;
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;
	UAuraAbilitySystemComponent* GetASC();

	FVector CachedDestination=FVector::ZeroVector;
	float FollowTime=0.f;
	float ShortPressThreshold=0.5f;
	bool bAutoRunning = false;
	bool bTargeting=false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius=50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent>Spline;

	void AutoRun();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};

