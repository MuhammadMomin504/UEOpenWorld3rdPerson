// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABird::ABird()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	capsule->SetCapsuleHalfHeight(20.f);
	capsule->SetCapsuleRadius(15.f);
	SetRootComponent(capsule);

	birdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Bird Mesh"));
	birdMesh->SetupAttachment(GetRootComponent());
	// if(cameraBoom)
	// {
	// 	cameraBoom->bEditableWhenInherited = true;
	// }

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	timeElapsed = 0.0f;
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABird::MoveForward(float value)
{
	if((Controller != nullptr) && (value != 0.f))
	{
		isGlideState = false;
		speedMultiplier = 2.0f;
		FVector forward = GetActorForwardVector();
		AddMovementInput(forward, value * speedMultiplier);

		// UE_LOG(LogTemp, Warning, TEXT("Value: %f"), speedMultiplier * value);
		// UE_LOG(LogTemp, Warning, TEXT("Forward Value: %s"), *forward.ToString());
		
	}
	else
	{
		isGlideState = true;
		speedMultiplier = 0.25f;
	}
	// UE_LOG(LogTemp, Warning, TEXT("Value: %f"), value);
}

void ABird::Turn(float value)
{
	// AddControllerYawInput(value);
	
	//UE_LOG(LogTemp, Warning, TEXT("Value: %f"), value);
}

void ABird::LookUp(float value)
{
	if((Controller != nullptr) && (value > 0.0f))
	{
		isMovingUp = false;
		isMovingDown = true;
		//when W key is pressed
	}
	else if(value < 0.0f)
	{
		//When S key is pressed
		isMovingUp = true;
		isMovingDown = false;
	}

	if(value == 0.0f)
	{
		isMovingUp = false;
		isMovingDown = false;
	}
	
	AddControllerPitchInput(value);
	
}

void ABird::TurnUsingKeys(float value)
{
	RotateMeshX(value);
	AddControllerYawInput(value * 0.5f);
	//UE_LOG(LogTemp, Warning, TEXT("Value: %f"), value);
}

float ABird::MoveTowards(float current, float target, float maxDelta)
{
	if(FMath::Abs(target - current) <= maxDelta)
	{
		return target;
	}
	return current + FMath::Sign(target - current) * maxDelta;
}


// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timeElapsed += DeltaTime * 0.5f;

	if(shouldResetRotation)
	{
		//FRotator currentRotation = birdMesh->GetRelativeRotation();
		FRotator currentRotation = birdMesh->GetRelativeRotation();;
		currentRotation.Pitch = MoveTowards(currentRotation.Pitch, 0.0f, 5.0f);

		if(isGlideState)
		{
			float sinRotation = FMath::Sin(timeElapsed * sineFrequency * 2.f * PI) * sineAmplitude;
			currentRotation.Roll = sinRotation;
		}
		if(birdMesh)
		{
			birdMesh->SetRelativeRotation(currentRotation);
		}
		
	}

	if(isGlideState)
	{
		FVector forward = GetActorForwardVector();
		
		AddMovementInput(forward, 1.0f * speedMultiplier);
	}
	

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABird::MoveForward);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ABird::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ABird::LookUp);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ABird::TurnUsingKeys);
	
}

void ABird::RotateMeshX(float axisValue)
{
	if(axisValue != 0.0f)
	{
		shouldResetRotation = false;
		FRotator currentRotation = birdMesh->GetRelativeRotation();
		currentRotation.Pitch += axisValue * pitchRotationSpeed * GetWorld()->GetDeltaSeconds();
		currentRotation.Pitch = FMath::Clamp(currentRotation.Pitch, -60.0f, 60.0f);
		birdMesh->SetRelativeRotation(currentRotation);
	}
	else
	{
		shouldResetRotation = true;
	}
}

