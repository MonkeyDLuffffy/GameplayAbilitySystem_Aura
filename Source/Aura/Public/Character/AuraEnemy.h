// copyright Druid bujingyun

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()

public:

	AAuraEnemy();

	/**Enemy Interface */
	virtual void HightlightActor() override;
	virtual  void UnHightlightActor() override;
	/**end Enemy Interface */

	/**Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/**end Combat Interface */

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	virtual void InitializeDefaultAttributes() const override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Default")
	int32 Level=1;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Default")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
