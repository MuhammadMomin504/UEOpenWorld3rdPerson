// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_GameMode.h"
#include "GameFramework/Actor.h"

ABatteryMan_GameMode::ABatteryMan_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABatteryMan_GameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABatteryMan_GameMode::SpawnPlayerRecharge,
		FMath::RandRange(2,5), true);
}

void ABatteryMan_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABatteryMan_GameMode::SpawnPlayerRecharge()
{
	float randX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float randY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	FVector spawnPosition = FVector(randX, randY, Spawn_Z);
	FRotator spawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	GetWorld()->SpawnActor(playerRecharge, &spawnPosition, &spawnRotation);
	 
}
