// copyright Druid bujingyun

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

struct FAuraGameplayTags;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellGlobeSelectedSignature, bool, bSendPointsButtonEnabled, bool,
                                             bEquipButtonEnabled, FString, DescriptionString, FString, NextLevelDescription);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForEquipSelectionSignature, const FGameplayTag&, AbilityType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpellGlobeReassignedSignature, const FGameplayTag&, AbilityTag);

struct FSelectAbility
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};
/**
 * 
 */
UCLASS()
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable,Category="GAS|SpellPoints")
	FOnPlayerStateChangedSignature SpellPointsChangedDelegate;

	//void UpgradeSpell(const )

	UPROPERTY(BlueprintAssignable)
	FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FWaitForEquipSelectionSignature WaitForEquipSelectionDelegate;

	UPROPERTY(BlueprintAssignable)
	FWaitForEquipSelectionSignature StopWaitingForEquipSelectionDelegate;

	UPROPERTY(BlueprintAssignable)
	FSpellGlobeReassignedSignature SpellGlobeReassignedDelegate;
	
	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);

	UFUNCTION(BlueprintCallable)
	void SpellGlobeDeselected();
	
	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed();

	UFUNCTION(BlueprintCallable)
	void EquipButtonPresses();

	UFUNCTION(BlueprintCallable)
	void SpellRowGlobePressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType);

	void OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& NewSlot, const FGameplayTag& PreviousSlot);
private:
 	static void ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSendSpellPointsButton, bool& bShouldEnableEquipButton);

	FSelectAbility SelectedAbility = {FAuraGameplayTags::Get().Abilities_None, FAuraGameplayTags::Get().Abilities_Status_Locked};
	int32 CurrentSpellPoints = 0;
	bool bWaitingForEquipSelection = false;

	FGameplayTag SelectedSlot;
};
