// copyright Druid bujingyun

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&,Info);


/**
 * 
 */
UCLASS()
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;

	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

	//UPROPERTY(BlueprintAssignable,Category="GAS|PlayStat")
	//FAttributeInfoSignature AttributeInfoDelegate;
	UPROPERTY(BlueprintAssignable,Category="GAS|AttributePoints")
	FOnPlayerStateChangedSignature AttributePointsChangeDelegate;


	UFUNCTION(BlueprintCallable)
	void UpgradeAttribute(const FGameplayTag& AttributeTag);
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:
	void BroadcastAttributeInfo(const FGameplayTag& GameplayTag,const FGameplayAttribute & Attribute) const;
};
