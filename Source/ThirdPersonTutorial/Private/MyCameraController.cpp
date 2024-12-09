// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCameraController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h" // For TActorIterator
#include "GameFramework/Actor.h"
#include "Bird.h"

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

	FName targetActorName = TEXT("BP_Bird_C_0");

	if(GetWorld())
	{
		for (TActorIterator<AActor> It(GetWorld()); It; ++It)
		{
			if(It->GetName() == targetActorName.ToString())
			{
				targetActor = *It;
				UE_LOG(LogTemp, Warning, TEXT("Target Actor found"));
				break;
			}
		}
	}
	
	if(targetActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target Actor: %s"), *targetActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Target Actor not set!"));
	}
	
}

// Called every frame
void AMyCameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(targetActor)
	{
		FVector targetLocation = targetActor->GetActorLocation();
		targetLocation.Z -= 30.0f; 
		FVector currentLocation = GetActorLocation();
		SetActorLocation(FMath::VInterpTo(currentLocation, targetLocation, DeltaTime, 2.0f));
	}

}

