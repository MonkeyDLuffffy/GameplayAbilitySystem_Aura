// copyright Druid bujingyun


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "AnalyticsEventAttribute.h"
#include "Kismet/KismetSystemLibrary.h"


TArray<FVector> UAuraSummonAbility::GetSpawnLocations() const
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FVector> SpawnLocations;
	
	if(NumMinions <= 0)
	{
		return TArray<FVector>();
	}
	if(NumMinions == 1)
	{
		SpawnLocations.Add(Location + Forward * (MaxSpawnDistance + MinSpawnDistance) / 2.f);
		return SpawnLocations;
	}
	
	const float DeltaSpread = SpawnSpread / (NumMinions - 1);
	
	const FVector RightOfSpread = Forward.RotateAngleAxis(SpawnSpread / 2.f, FVector::UpVector);
	
	for(int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = RightOfSpread.RotateAngleAxis(-DeltaSpread*i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(
			Hit,
			ChosenSpawnLocation + FVector(0.f, 0.f, 400.f),
			ChosenSpawnLocation - FVector(0.f, 0.f, 400.f),
			ECC_Visibility
			);
		if(Hit.bBlockingHit)
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}
		SpawnLocations.Add(ChosenSpawnLocation);
		
	}
	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass()
{
 	const int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];
}
