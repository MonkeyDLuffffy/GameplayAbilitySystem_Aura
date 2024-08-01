// copyright Druid bujingyun

#pragma once

#include <tiff.h>

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraHUD.generated.h"

class USpellMenuWidgetController;
class UAuraUserWidget;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;
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



	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WSParams);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WSParams);

	USpellMenuWidgetController* GetSpellMenuWidgetController(const FWidgetControllerParams& WSParam);

	//UMenuWidgetController
	void InitOverlay(APlayerController * PC,APlayerState * PS,UAbilitySystemComponent* ASC,UAttributeSet* AS);

protected:


private:

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWightClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController>OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController>AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController>AttributeMenuWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<USpellMenuWidgetController> SpellMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<USpellMenuWidgetController> SpellMenuWidgetControllerClass;
	
};
