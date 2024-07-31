// copyright Druid bujingyun

#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet * AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto & Pair:AuraAttributeSet->TagsToAttributeMap)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
	[this,Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key,Pair.Value());
		});
	}

	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnAttributePointsChangedDelegate.AddLambda(
		[this](const int32 NewPoints)
		{
			AttributePointsChangeDelegate.Broadcast(NewPoints);
		}
	);
	AuraPlayerState->OnSpellPointsChangedDelegate.AddLambda(
		[this](const int32 NewPoints)
		{
			SpellPointsChangeDelegate.Broadcast(NewPoints);
		}
	);
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet * AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto & Pair : AuraAttributeSet->TagsToAttributeMap)
	{
		BroadcastAttributeInfo(Pair.Key,Pair.Value());
	}

	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AttributePointsChangeDelegate.Broadcast(AuraPlayerState->GetAttributePoints());
	SpellPointsChangeDelegate.Broadcast(AuraPlayerState->GetSpellPoints());
	
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	if(UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		AuraASC->UpgradeAttribute(AttributeTag);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& GameplayTag,
                                                            const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info=AttributeInfo->FindAttributeInfoForTag(GameplayTag);
	Info.AttributeValue=Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}





