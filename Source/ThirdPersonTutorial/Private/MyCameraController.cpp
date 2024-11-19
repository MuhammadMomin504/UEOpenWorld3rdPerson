// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCameraController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyCameraController::AMyCameraController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if(springArm)
		springArm->SetupAttachment(RootComponent);

	SetRootComponent(springArm);
	cameraBoom = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if(cameraBoom && springArm)
	{
		cameraBoom->SetupAttachment(springArm);
	}
	
}

// Called when the game starts or when spawned
void AMyCameraController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

