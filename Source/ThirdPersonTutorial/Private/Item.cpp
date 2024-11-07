// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "DrawDebugHelpers.h"
#include "ThirdPersonTutorial/ThirdPersonTutorial.h"
#include "GameFramework/Actor.h"

#define THIRTY 30


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = itemMesh;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	currentPosition = GetActorLocation();
	//SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 100.0f));

	// UE_LOG(LogTemp, Warning, TEXT("Begin Play called!"));
	//
	// if(GEngine)
	// {
	// 	GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, FString("Item OnScreen Message!"));
	// }
	//
	//
	// FVector location = GetActorLocation();
	// location.Z = 50.0f;
	// SetActorLocation(location);
	//
	// FRotator myNewRotation = GetActorRotation();
	// myNewRotation.Yaw = 45.0f;
	// SetActorRotation(myNewRotation);
	//
	//
	// UWorld* World = GetWorld();
	// FVector Location = GetActorLocation();
	// DRAW_SPHERE(Location);
	
}

float AItem::TransformSin(float value)
{
	return amplitude * FMath::Sin(value * timeConstant);
}

float AItem::TransformCos(float value)
{
	return  amplitude * FMath::Cos(value * timeConstant);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	runningTime += DeltaTime;
	//float deltaZ = amplitude * FMath::Sin(runningTime * timeConstant);
	
	// AddActorWorldOffset(FVector(0.f, 0.f, TransformSin(runningTime)));
	// AddActorWorldOffset(FVector(TransformCos(runningTime), 0.f, 0.f));
	//
	// DRAW_SPHERE_SingleFrame(GetActorLocation());
	// DRAW_VECTOR_SingleFrame(GetActorLocation(), GetActorLocation() +  GetActorForwardVector() * 100.f);
	//
	// FVector avgVector = Avg<FVector>(GetActorLocation(), FVector::ZeroVector);
	// DRAW_SPHERE_SingleFrame(avgVector);
	
	 SetLocationOffset(DeltaTime);
	 RotateObject(DeltaTime);
	
	//DebugCode(DeltaTime);

	
}

void AItem::DebugCode(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Delta Time = %f"), DeltaTime);
	
	if(GEngine)
	{
		FString Name = GetName();
		FString message = FString::Printf(TEXT("Item Name: %s"), *Name);
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, message);
		UE_LOG(LogTemp, Warning, TEXT("Item Name = %s"), *Name);
	}
}

void AItem::SetLocationOffset(float DeltaTime)
{
	//Movement rate in units of cm/s
	float movementRate = 5.0f;
	
	FVector targetPosition = FVector(TransformSin(runningTime), 0.f, 0.f);
	//SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0.0f));
	//MovementRate * DeltaTime (cm/s) * (s/frame) = cm/frame
	AddActorWorldOffset(targetPosition);
}

void AItem::RotateObject(float DeltaTime)
{
	float rotationRate = 45.0f;
	AddActorWorldRotation(FRotator(0.f, rotationRate * DeltaTime, 0.f));
}

