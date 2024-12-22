// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCameraController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h" // For TActorIterator
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


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

	cameraOffset = FVector(-50.0f, 0.0f, 50.0f);
	smoothSpeed = 5.0f;
}



// Called when the game starts or when spawned
void AMyCameraController::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		// Smoothly switch to the new camera
		PlayerController->SetViewTargetWithBlend(this, 1.0f); // Blend time: 1 second
	}

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

void AMyCameraController::Turn(float value)
{
	//AddControllerYawInput(value);
}

void AMyCameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//PlayerInputComponent->BindAxis(FName("Turn"), this, &AMyCameraController::Turn);
}

// Called every frame
void AMyCameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(targetActor)
	{
		FVector targetLocation = targetActor->GetActorLocation() + cameraOffset;
		FVector currentLocation = GetActorLocation();

		FVector directionVector = targetActor->GetActorLocation() - GetActorLocation();
		directionVector.Normalize();

		FRotator desiredRotation = directionVector.Rotation();
		FRotator newRotation = FMath:: RInterpTo(GetActorRotation(), desiredRotation,DeltaTime, smoothSpeed);
		
		SetActorLocation(FMath::VInterpTo(currentLocation, targetLocation, DeltaTime, smoothSpeed));
		SetActorRotation(newRotation);
	}

}

