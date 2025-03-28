// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h" // For TActorIterator
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "CameraControllerPawnClass.h"

// Sets default values
ACameraControllerPawnClass::ACameraControllerPawnClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

	springArm->bEnableCameraLag = true;
	springArm->bUsePawnControlRotation = true;

	cameraOffset = FVector(-50.0f, 0.0f, 50.0f);
	smoothSpeed = 5.0f;
}

// Called when the game starts or when spawned
void ACameraControllerPawnClass::BeginPlay()
{
	Super::BeginPlay();

	Super::BeginPlay();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		EnableInput(PlayerController);
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

void ACameraControllerPawnClass::Turn(float value)
{
	if(Controller != nullptr)
	{
		// FRotator NewRotation = springArm->GetRelativeRotation();
		// NewRotation.Yaw += value * 5.0f * GetWorld()->GetDeltaSeconds();
		// springArm->SetRelativeRotation(NewRotation);
		UE_LOG(LogTemp, Warning, TEXT("Yaw Value: %f"), value);
		AddControllerYawInput(value);
		
	}
}

void ACameraControllerPawnClass::LookUp(float value)
{
	if(Controller != nullptr)
	{
		// FRotator NewRotation = springArm->GetRelativeRotation();
		// NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + value * 5.0f * GetWorld()->GetDeltaSeconds(), -80.f, 80.f);
		// springArm->SetRelativeRotation(NewRotation);
		UE_LOG(LogTemp, Warning, TEXT("Pitch Value: %f"), value);
		AddControllerPitchInput(value);
	}

}

// Called every frame
void ACameraControllerPawnClass::Tick(float DeltaTime)
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
		//SetActorRotation(newRotation);
	}

	
}

// Called to bind functionality to input
void ACameraControllerPawnClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ACameraControllerPawnClass::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ACameraControllerPawnClass::LookUp);
}

