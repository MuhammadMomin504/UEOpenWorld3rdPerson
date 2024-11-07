// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestCharacter.h"

// Sets default values
AMyTestCharacter::AMyTestCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyTestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

