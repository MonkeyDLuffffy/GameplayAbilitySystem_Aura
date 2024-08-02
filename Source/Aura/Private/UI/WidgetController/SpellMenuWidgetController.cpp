// copyright Druid bujingyun


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "NativeGameplayTags.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	SpellPointsChangedDelegate.Broadcast(GetAuraPS()->GetSpellPoints());

}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetAuraASC()->AbilityStatusChanged.AddLambda(
		[this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 NewLevel)
		{
			if(SelectedAbility.Ability.MatchesTag(AbilityTag))
			{
				SelectedAbility.Status = StatusTag;
				bool bEnableSendPoints = false;
				bool bEnableEquip  = false;
				ShouldEnableButtons(SelectedAbility.Status, CurrentSpellPoints, bEnableSendPoints, bEnableEquip);
				FString Description;
				FString NextLevelDescription;
				GetAuraASC()->GetDescriptionsByAbilityTag(AbilityTag, Description, NextLevelDescription);
				SpellGlobeSelectedDelegate.Broadcast(bEnableSendPoints, bEnableEquip, Description, NextLevelDescription);
			}
			
			if(AbilityInfo)
			{
				FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
				Info.StatusTag = StatusTag;
				AbilityInfoDelegate.Broadcast(Info);
			}
		}
	);

	/*将技能点广播到事件调度器（动态多播委托）*/
	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda(
[this](const int32 NewPoints)
	{
		SpellPointsChangedDelegate.Broadcast(NewPoints);
	
		CurrentSpellPoints = NewPoints;
		bool bEnableSendPoints = false;
		bool bEnableEquip  = false;
		ShouldEnableButtons(SelectedAbility.Status, CurrentSpellPoints, bEnableSendPoints, bEnableEquip);
		FString Description;
		FString NextLevelDescription;
		GetAuraASC()->GetDescriptionsByAbilityTag(SelectedAbility.Ability, Description, NextLevelDescription);
		SpellGlobeSelectedDelegate.Broadcast(bEnableSendPoints, bEnableEquip, Description, NextLevelDescription);
	});
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	if(!AbilityTag.IsValid())
	{
		return;
	}
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	const int32 SpellPoints = GetAuraPS()->GetSpellPoints();
	FGameplayTag AbilityStatus;
	
	const bool bTagValid = AbilityTag.IsValid();
	const bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
	const FGameplayAbilitySpec* AbilitySpec =  GetAuraASC()->GetSpecFromAbilityTag(AbilityTag);
	const bool bSpecValid = AbilitySpec!= nullptr;
	if(!bTagValid || bTagNone || !bSpecValid)
	{
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		AbilityStatus = GetAuraASC()->GetStatusTagFromSpec(*AbilitySpec);
	}

	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = AbilityStatus;

	bool bEnableSendPoints = false;
	bool bEnableEquip  = false;
	ShouldEnableButtons(AbilityStatus, SpellPoints, bEnableSendPoints, bEnableEquip);

	FString Description;
	FString NextLevelDescription;
	GetAuraASC()->GetDescriptionsByAbilityTag(AbilityTag, Description, NextLevelDescription);
	SpellGlobeSelectedDelegate.Broadcast(bEnableSendPoints, bEnableEquip, Description, NextLevelDescription);
}

void USpellMenuWidgetController::SpendPointButtonPressed()
{
	if(GetAuraASC())
	{
		GetAuraASC()->ServerSpendSpellPoint(SelectedAbility.Ability);
	}
	
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints,
                                                     bool& bShouldEnableSendSpellPointsButton, bool& bShouldEnableEquipButton)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	bShouldEnableSendSpellPointsButton = false;
	bShouldEnableEquipButton = false;
	if(AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
	{
		bShouldEnableEquipButton = true;
		if(SpellPoints > 0)
		{
			bShouldEnableSendSpellPointsButton = true;
		}
	}
	else if(AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		if(SpellPoints > 0)
		{
			bShouldEnableSendSpellPointsButton = true;
		}
	}
	else if(AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bShouldEnableEquipButton = true;
		if(SpellPoints > 0)
		{
			bShouldEnableSendSpellPointsButton = true;
		}
	}
}
