// copyright Druid bujingyun


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WSParams)
{
	if(OverlayWidgetController==nullptr)
	{
		this->OverlayWidgetController=NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		this->OverlayWidgetController->SetWidgetControllerParams(WSParams);
		return this->OverlayWidgetController;
	}
	return this->OverlayWidgetController;
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
	OverlayWidget->AddToViewport();



	

	check(OverlayWidget);
}


