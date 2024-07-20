// copyright Druid bujingyun

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

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
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet * AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto & Pair : AuraAttributeSet->TagsToAttributeMap)
	{
		BroadcastAttributeInfo(Pair.Key,Pair.Value());
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& GameplayTag,
	const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info=AttributeInfo->FindAttributeInfoForTag(GameplayTag);
	Info.AttributeValue=Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}





