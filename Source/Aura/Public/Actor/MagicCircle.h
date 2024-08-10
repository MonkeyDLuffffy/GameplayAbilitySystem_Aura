// copyright Druid bujingyun

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicCircle.generated.h"

UCLASS()
class AURA_API AMagicCircle : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AMagicCircle();
	virtual void Tick(float DeltaTime) override;

	void SetDecalMaterial(UMaterialInterface* DecalMaterial = nullptr);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDecalComponent> MagicCircleDecal;


};
