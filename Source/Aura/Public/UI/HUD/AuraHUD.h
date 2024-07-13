// copyright Druid bujingyun

#pragma once

#include <tiff.h>

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
class UOverlayWidgetController;
struct FWidgetControllerParams;
class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UOverlayWidgetController * GetOverlayWidgetController(const FWidgetControllerParams&WSParams);

	void InitOverlay(APlayerController * PC,APlayerState * PS,UAbilitySystemComponent *ASC,UAttributeSet*AS);

protected:


private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWightClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController>OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
};
