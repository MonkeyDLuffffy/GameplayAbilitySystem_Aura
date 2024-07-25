// copyright Druid bujingyun


#include "AI/BTService_FindNearestPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const APawn* OwningPawn = AIOwner->GetPawn();

	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetTag, ActorsWithTag);

	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr; 
	for(AActor* TargetActor : ActorsWithTag)
	{
		if(IsValid(TargetActor))
		{
			const float DistanceTemp = (TargetActor->GetActorLocation() - OwningPawn->GetActorLocation()).Length();
			if(ClosestDistance > DistanceTemp)
			{
				ClosestActor = TargetActor;
				ClosestDistance = DistanceTemp;
			}
		}
	}
	UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetToFollowSelector, ClosestActor);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTargetSelector, ClosestDistance);

	if(ClosestActor == nullptr )return;
	const FString& Msg=FString::Printf(TEXT("ClosestActor : %s ,ClosestDistance : %f"),*ClosestActor->GetName(),ClosestDistance);
	GEngine->AddOnScreenDebugMessage(1,5.f,FColor::Red,Msg);
}
