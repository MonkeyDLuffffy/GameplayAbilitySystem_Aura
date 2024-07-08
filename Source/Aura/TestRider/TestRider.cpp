// Fill out your copyright notice in the Description page of Project Settings.


#include "TestRider/TestRider.h"

// Sets default values
ATestRider::ATestRider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestRider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestRider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

