// copyright Druid bujingyun

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

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

	
	UPROPERTY(BlueprintReadOnly)
	bool bHightlight=false;

protected:
	virtual void BeginPlay() override;
};
