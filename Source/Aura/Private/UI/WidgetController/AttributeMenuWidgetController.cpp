// copyright Druid bujingyun

#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo);
	for (auto & Pair:GetAuraAS()->TagsToAttributeMap)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
	[this,Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key,Pair.Value());
		});
	}
	
	GetAuraPS()->OnAttributePointsChangedDelegate.AddLambda(
		[this](const int32 NewPoints)
		{
			AttributePointsChangeDelegate.Broadcast(NewPoints);
		}
	);

}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo);

	for (auto & Pair : GetAuraAS()->TagsToAttributeMap)
	{
		BroadcastAttributeInfo(Pair.Key,Pair.Value());
	}
	
	AttributePointsChangeDelegate.Broadcast(GetAuraPS()->GetAttributePoints());
	
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	GetAuraASC()->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& GameplayTag,
                                                            const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info=AttributeInfo->FindAttributeInfoForTag(GameplayTag);
	Info.AttributeValue=Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}





