// copyright Druid bujingyun


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
//#include "Axis.h"
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
	

	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}


void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem * Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	check(Subsystem);

	Subsystem->AddMappingContext(AuraContext,0);

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
	UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);


	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
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

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if(!CursorHit.bBlockingHit) return;

	LastActor =ThisActor;
	ThisActor=	Cast<IEnemyInterface>(CursorHit.GetActor());
	
	/** 
	 * 射线光标有几种情况
	 * 1.lastActor和thisActor都为空，啥也不做
	 * 2.lastActor为空，但是thisActor是可用的，高亮thisActor
	 * 3.lastActor可用，但是ThisActor为空，取消LastActor的高亮
	 * 4.lastActor和ThisActor都是可用的，他们不是同一个，高亮thisActor，取消LastActor的高亮
	 * 5.lastActor和ThisActor都是可用的，他们相同，啥也不做
	 */
	if(LastActor==nullptr)
	{
		if(ThisActor!=nullptr)
		{
			//2
			ThisActor->HightlightActor();
		}
		else
		{
			//1
		}
	}
	else
	{
		if(ThisActor==nullptr)
		{
			//3
			LastActor->UnHightlightActor();
		}
		else
		{
			if(LastActor!=ThisActor)
			{
				//4
				ThisActor->HightlightActor();
				LastActor->UnHightlightActor();
			}
			else
			{
				//5
			}
		}
	}
}
