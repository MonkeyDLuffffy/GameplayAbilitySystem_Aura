// copyright Druid bujingyun

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraWidgetController.generated.h"

class UPanelWidget;
class UAttributeSet;
class UAbilitySystemComponent;
class APlayerController;
class APlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChangedSignature, int32 ,NewValue);
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController=nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState=nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent=nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAttributeSet>AttributeSet=nullptr;

	
	FWidgetControllerParams()
	{
		
	}
	
	FWidgetControllerParams( APlayerController * PC,  APlayerState * PS, UAbilitySystemComponent *ASC,UAttributeSet*AS):
	PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS)
	{
		
	}
	
};
/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();

	virtual void BindCallbacksToDependencies();
protected:
	UPROPERTY(BlueprintReadOnly,Category="WightController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly,Category="WightController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly,Category="WightController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly,Category="WightController")
	TObjectPtr<UAttributeSet>AttributeSet;

	UFUNCTION(BlueprintCallable, Category = "WidgetController")
	static void SetAllChildrenWidgetController(const UPanelWidget* WidgetPanel,UObject* WidgetController);
};
