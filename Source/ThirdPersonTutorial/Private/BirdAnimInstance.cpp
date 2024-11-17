// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdAnimInstance.h"
#include "Bird.h"

void UBirdAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BirdObject = Cast<ABird>(TryGetPawnOwner());

	
	
}

void UBirdAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(BirdObject)
	{
		birdSpeedMultiplier = BirdObject-> GetSpeedMultiplier();
		isMovingUp = BirdObject-> GetMovingUp();
		isMovingDown = BirdObject-> GetMovingDown();

		//UE_LOG(LogTemp, Warning, TEXT("Value:"));
	}
	
}
