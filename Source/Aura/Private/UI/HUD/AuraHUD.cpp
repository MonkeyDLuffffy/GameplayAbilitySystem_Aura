// copyright Druid bujingyun


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WSParams)
{
	if(OverlayWidgetController==nullptr)
	{
		this->OverlayWidgetController=NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		this->OverlayWidgetController->SetWidgetControllerParams(WSParams);
		this->OverlayWidgetController->BindCallbacksToDependencies();
	}
	return this->OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WSParams)
{
	if(AttributeMenuWidgetController==nullptr)
	{
		this->AttributeMenuWidgetController=NewObject<UAttributeMenuWidgetController>(this,AttributeMenuWidgetControllerClass);
		this->AttributeMenuWidgetController->SetWidgetControllerParams(WSParams);
		this->AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return this->AttributeMenuWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController * PC,APlayerState * PS,UAbilitySystemComponent *ASC,UAttributeSet*AS)
{
	checkf(OverlayWightClass,TEXT("Overlay Widget class uninitialized, please fill out BP AuraHUD"));
	checkf(OverlayWidgetControllerClass,TEXT("Overlay Widget Controller class uninitialized, please fill out BP AuraHuD"));
	UUserWidget* widget= CreateWidget<UUserWidget>(GetWorld(),OverlayWightClass);
	OverlayWidget=Cast<UAuraUserWidget>(widget);
	
	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	UOverlayWidgetController* WidgetController=GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	
	WidgetController->BroadcastInitialValues();
	
	OverlayWidget->AddToViewport();
	
}


