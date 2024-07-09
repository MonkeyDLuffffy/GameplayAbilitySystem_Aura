// copyright Druid bujingyun


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
}

void AAuraEnemy::HightlightActor()
{
	//bHightlight=true;
	GetMesh()->SetRenderCustomDepth((true));
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

void AAuraEnemy::UnHightlightActor()
{
	//bHightlight=false;
	GetMesh()->SetRenderCustomDepth((false));
	Weapon->SetRenderCustomDepth(false);
}
