// copyright Druid bujingyun

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();


	/**Player Interface*/
	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	virtual int32 GetXP_Implementation() const override;
	virtual int32 FindLevelForXP_Implementation(const int32 InXP) override;
	virtual int32 GetAttributePointsReward_Implementation(const int Level) const override;
	virtual int32 GetSpellPointsReward_Implementation(const int Level) const override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) const override;
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) const override;
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) const override;
	virtual int32 GetAttributePoints_Implementation() const override;
	virtual int32 GetSpellPoints_Implementation() const override;
	virtual void ShowMagicCircle_Implementation(UMaterialInterface* DecalMaterial) override;
	virtual void HideMagicCircle_Implementation() override;
	virtual void SaveProgress_Implementation(const FName& CheckpointTag) override;
	/**End Player Interface*/
	
	
	/**Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() override;
	/**end Combat Interface */
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;



private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
protected:
	virtual void InitAbilityActorInfo() override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpParticles() const;

	virtual  void OnRep_Stunned() override;
	virtual void OnRep_Burned() override;

};
