// copyright Druid bujingyun


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Actor/MagicCircle.h"
#include "Aura/Aura.h"
#include "Aura/AuraLogChannels.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"
//#include "Aura/Public/Actor/MagicCircle.h"


//#include "Axis.h"
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
	LastActor=nullptr;
	ThisActor=nullptr;

	Spline=CreateDefaultSubobject<USplineComponent>("Spline");
	
}

FVector AAuraPlayerController::GetMouseCursorLocation() const
{
	return CursorHit.Location;
}

bool AAuraPlayerController::FindMouseResultHit(FHitResult& HitResult) const
{
	HitResult = CursorHit;
	return HitResult.bBlockingHit;
}


void AAuraPlayerController::ShowMagicCircle(UMaterialInterface* DecalMaterial)
{
	if(!IsValid(MagicCircle))
	{
		MagicCircle = GetWorld()->SpawnActor<AMagicCircle>(MagicCircleClass);
		bShowMouseCursor = false;
		if(DecalMaterial != nullptr)
		{
			MagicCircle->SetDecalMaterial(DecalMaterial);
			
		}
	}
		
}

void AAuraPlayerController::HideMagicCircle()
{
	if(IsValid(MagicCircle))
	{
		MagicCircle->Destroy();
	}
	bShowMouseCursor = true;
		
}

void AAuraPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter,const bool bIsBlockedHit,const bool bIsCriticalHit)
{
	if(IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bIsBlockedHit, bIsCriticalHit);
	}
}


void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRun();
	UpdateMagicCircleLocation();
}

void AAuraPlayerController::CursorTrace()
{
	if(GetASC() && GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_CursorTrace))
	{
		if(LastActor) LastActor->UnHightlightActor();
		if(ThisActor) ThisActor->HightlightActor();
		LastActor = nullptr;
		ThisActor = nullptr;
		return;
	}

	const ECollisionChannel TraceChannel = IsValid(MagicCircle)? ECC_ExcludePlayers : ECC_Visibility;
	GetHitResultUnderCursor(TraceChannel,false,CursorHit);


	
	if(!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor=	Cast<IEnemyInterface>(CursorHit.GetActor());

	if(LastActor != ThisActor)
	{
		if(LastActor) LastActor->UnHightlightActor();
		if(ThisActor) ThisActor->HightlightActor();
	}
}

void AAuraPlayerController::AutoRun()
{
	if(bAutoRunning)
	{
		if(APawn * ControlledPawn = GetPawn())
		{
			const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(),ESplineCoordinateSpace::World);
			const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);
			ControlledPawn->AddMovementInput(Direction);

			const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
			if(DistanceToDestination <= AutoRunAcceptanceRadius)
			{
				bAutoRunning = false;
			}
		}
	}
}

void AAuraPlayerController::UpdateMagicCircleLocation()
{
	if(IsValid(MagicCircle))
	{
		MagicCircle->SetActorLocation(CursorHit.ImpactPoint);
	}
}



void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem * Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if(Subsystem) Subsystem->AddMappingContext(AuraContext,0);
	
	bShowMouseCursor=true;  
	DefaultMouseCursor=EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);

	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);

	UAuraInputComponent * AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	AuraInputComponent->BindAction(ShiftAction,ETriggerEvent::Started,this,&AAuraPlayerController::ShiftPressed);
	AuraInputComponent->BindAction(ShiftAction,ETriggerEvent::Completed,this,&AAuraPlayerController::ShiftReleased);
	
	AuraInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	if(GetASC() && GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))
	{
		return;
	}
	const FVector2D InputAxisVector =InputActionValue.Get<FVector2D>();
	const FRotator Rotation=GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	if(APawn * ControllerPawn=GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
	
}




void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{

	if(GetASC() && GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))
	{
		return;;
	}
	
	if(InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false ;
		bAutoRunning = false ;
	}
	if (GetASC()) GetASC()->AbilityInputTagPressed(InputTag);
	//GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Red,*InputTag.ToString());
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if(GetASC() && GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputReleased))
	{
		return;
	}
	
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if(GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}

	if(GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	
	if(!bTargeting && !bShiftKeyDown)
	{
		const APawn * ControlledPawn = GetPawn();
		if(FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			
			if(const UNavigationPath *NavPath= UNavigationSystemV1::FindPathToLocationSynchronously(this,ControlledPawn->GetActorLocation(),CachedDestination))
			{
				Spline->ClearSplinePoints();
				for(const FVector & PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc,ESplineCoordinateSpace::World);
				}
				
				if(NavPath->PathPoints.Num() > 0)
				{
					bAutoRunning = true;
					CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num()-1];
				}
				
			}
			if(GetASC() && !GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputPressed))
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ClickNiagaraSystem, CachedDestination);
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{

	if(GetASC() && GetASC()->HasMatchingGameplayTag(FAuraGameplayTags::Get().Player_Block_InputHeld))
	{
		return;
	}
	
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if(GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}

	if(bTargeting || bShiftKeyDown)
	{
		if(GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		if(CursorHit.bBlockingHit) CachedDestination=CursorHit.ImpactPoint;
		
		if(APawn * ControlledPawn=GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if(this->AuraAbilitySystemComponent == nullptr)
	{
		this->AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	
	return this->AuraAbilitySystemComponent;
}

