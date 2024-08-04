// copyright Druid bujingyun


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	
	OnHealthChanged.Broadcast(GetAuraAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetAuraAS()->GetMaxHealth());
	OnManaChanged.Broadcast(GetAuraAS()->GetMana());
	OnMaxManaChanged.Broadcast(GetAuraAS()->GetMaxMana());
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	AAuraPlayerState* AuraPS = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPS->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	AuraPS->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel)
	{
		OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data )
	{
			OnHealthChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data )
	{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data )
	{
			OnManaChanged.Broadcast(Data.NewValue);
	});

		
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetMaxManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data )
	{
			OnMaxManaChanged.Broadcast(Data.NewValue);
	});
	
	if(GetAuraASC())
	{

		GetAuraASC()->AbilityEquipped.AddUObject(this, &UOverlayWidgetController::OnAbilityEquipped);
		
		/*确保OnInitializeStartupAbilities一定且仅被调用一次*/
		if(GetAuraASC()->bStartupAbilitiesGiven)
		{
			BroadcastAbilityInfo();
		}
		else
		{
			GetAuraASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
		}
		
		GetAuraASC()->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag :AssetTags)
				{
					FGameplayTag MessageTag=FGameplayTag::RequestGameplayTag(FName("Message"));
					if(!Tag.MatchesTag(MessageTag)) continue;
			
					//Todo: Broadcast the tag to the Widget Controller
					const FString& Msg=FString::Printf(TEXT("GE Tag: %s"),*Tag.ToString());
					//GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Yellow,Msg);
					const FUIWidgetRow* UIWidgetRow=	GetDataTableRowByTag <FUIWidgetRow> (this->MessageWidgetDataTable,Tag);
					MessageWidgetRowDelegate.Broadcast(*UIWidgetRow);
				}
			}
		);
		
	}

}

void UOverlayWidgetController::OnXPChanged(int32 NewXP)
{
	const ULevelUpInfo* LevelUpInfo = GetAuraPS()->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("Unabled to find LevelUpInfo. Please fill out AuraPlayerState Blueprint"));

	int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	int32 MaxLevel = LevelUpInfo->LevelUpInfos.Num();
	
	if(Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInfos[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInfos[Level - 1].LevelUpRequirement;
		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);
		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
	
}

void UOverlayWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
	const FGameplayTag& NewSlot, const FGameplayTag& PreviousSlot) const
{

	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	FAuraAbilityInfo LastSlotInfo;
	LastSlotInfo.StatusTag = GameplayTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag = PreviousSlot;
	LastSlotInfo.AbilityTag = GameplayTags.Abilities_None;
	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = NewSlot;
	AbilityInfoDelegate.Broadcast(Info);
}
