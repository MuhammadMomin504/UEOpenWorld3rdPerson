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
	if(cameraBoom)
	{
		cameraBoom->bEditableWhenInherited = true;
	}

	AutoPossessPlayer = EAutoReceiveInput::Player0;
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
		FVector forward = GetActorForwardVector();
		AddMovementInput(forward, value);
	}
	//UE_LOG(LogTemp, Warning, TEXT("Value: %f"), value);
}

void ABird::Turn(float value)
{
	AddControllerYawInput(value);
	UE_LOG(LogTemp, Warning, TEXT("Value: %f"), value);
}

void ABird::LookUp(float value)
{
	AddControllerPitchInput(value);
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABird::MoveForward);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ABird::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ABird::LookUp);
}

