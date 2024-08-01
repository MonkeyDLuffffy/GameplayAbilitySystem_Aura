// copyright Druid bujingyun


#include "UI/WidgetController/AuraWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/PanelWidget.h"
#include "Components/Widget.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "UI/Widget/AuraUserWidget.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	this->PlayerController = WCParams.PlayerController;
	this->PlayerState = WCParams.PlayerState;
	this->AbilitySystemComponent = WCParams.AbilitySystemComponent;
	this->AttributeSet = WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
	
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}

void UAuraWidgetController::BroadcastAbilityInfo()
{
	if(!GetAuraASC()->bStartupAbilitiesGiven) return;
	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
	{
		FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(UAuraAbilitySystemComponent::GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = GetAuraASC()->GetInputTagFromSpec(AbilitySpec);
		Info.StatusTag = GetAuraASC()->GetStatusTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});

	GetAuraASC()->ForEachAbility(BroadcastDelegate);
}

AAuraPlayerController* UAuraWidgetController::GetAuraPC()
{
	if(AuraPlayerController == nullptr)
	{
		AuraPlayerController = Cast<AAuraPlayerController>(PlayerController);
	}
	return AuraPlayerController;
}

AAuraPlayerState* UAuraWidgetController::GetAuraPS()
{
	if(AuraPlayerState == nullptr)
	{
		AuraPlayerState = Cast<AAuraPlayerState>(PlayerState);
	}
	return AuraPlayerState;
}

UAuraAbilitySystemComponent* UAuraWidgetController::GetAuraASC()
{
	if(AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	}
	return AuraAbilitySystemComponent;
}

UAuraAttributeSet* UAuraWidgetController::GetAuraAS()
{
	if(AuraAttributeSet == nullptr)
	{
		AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	}
	return AuraAttributeSet;
}

void UAuraWidgetController::SetAllChildrenWidgetController(const UPanelWidget* WidgetPanel, UObject* WidgetController)
{
	TArray<UWidget*> Widgets = WidgetPanel->GetAllChildren();
	for (UWidget* Widget : Widgets)
	{
		if(UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(Widget))
		{
			AuraUserWidget->SetWidgetController(WidgetController);
		}
		else if(const UPanelWidget* PanelWidgetChild = Cast<UPanelWidget>(Widget))
		{
			SetAllChildrenWidgetController(PanelWidgetChild, WidgetController);
		}
	}
}
