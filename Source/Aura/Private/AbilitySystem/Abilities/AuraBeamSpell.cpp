// copyright Druid bujingyun


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraBeamSpell::StoreMouseDataInfo(const FHitResult& HitResult)
{
	if(HitResult.bBlockingHit) 
	{
		MouseHitLocation = HitResult.Location;
		MouseHitActor = HitResult.GetActor();
	}
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}

void UAuraBeamSpell::StoreOwnerVariables()
{
	if(CurrentActorInfo)
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
		OwnerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor); 
	}
}

void UAuraBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation, float Radius)
{
	check(OwnerCharacter);
	if(OwnerCharacter->Implements<UCombatInterface>())
	{
		if(USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerCharacter))
		{
			const FVector SocketLocation = Weapon->GetSocketLocation(FName("TipSocket"));
			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(OwnerCharacter);
			FHitResult HitResult;
			UKismetSystemLibrary::SphereTraceSingle(
				OwnerCharacter,
				SocketLocation,
				BeamTargetLocation,
				Radius,
				TraceTypeQuery1,
				false,
				ActorsToIgnore,
				EDrawDebugTrace::None,
				HitResult,
				true);
			if(HitResult.bBlockingHit)
			{
				MouseHitLocation = HitResult.Location;
				MouseHitActor = HitResult.GetActor();
			}
		}
		
	}
	if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(MouseHitActor))
	{
		if(!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::PrimatyTargetDied))
		{
			CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UAuraBeamSpell::PrimatyTargetDied);
		}
		
	}
}

void UAuraBeamSpell::StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	ActorsToIgnore.Add(MouseHitActor);
	
	TArray<AActor*> OverlappingActors;
	UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(GetAvatarActorFromActorInfo(), OverlappingActors, ActorsToIgnore, ShockTargetRadius, MouseHitActor->GetActorLocation(), GetAvatarActorFromActorInfo());

	UAuraAbilitySystemLibrary::GetClosestTargets(GetNumSpellsEffect(), OverlappingActors, OutAdditionalTargets, MouseHitActor->GetActorLocation());
	for (AActor* Target : OutAdditionalTargets)
	{
		if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(Target))
		{
			if(!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::AdditionalTargetDied))
			{
				CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UAuraBeamSpell::AdditionalTargetDied);
			}
		}
	}
}

int32 UAuraBeamSpell::GetNumSpellsEffect(int InLevel) const
{
	if(bUseMaxNumSpellsEffect) return MaxNumSpellsEffect - 1;
	return InLevel < 1 ? FMath::Min(GetAbilityLevel() - 1, MaxNumSpellsEffect - 1) :  FMath::Min(InLevel - 1, MaxNumSpellsEffect - 1);
}

