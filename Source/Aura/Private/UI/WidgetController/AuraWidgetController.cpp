// copyright Druid bujingyun


#include "UI/WidgetController/AuraWidgetController.h"

#include "Components/PanelWidget.h"
#include "Components/Widget.h"
#include "UI/Widget/AuraUserWidget.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	this->PlayerController=WCParams.PlayerController;
	this->PlayerState=WCParams.PlayerState;
	this->AbilitySystemComponent=WCParams.AbilitySystemComponent;
	this->AttributeSet=WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
	
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
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
