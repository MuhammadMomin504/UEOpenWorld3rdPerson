// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BirdAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTUTORIAL_API UBirdAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	class ABird* BirdObject;

	UPROPERTY(BlueprintReadOnly, Category ="Movement")
	float birdSpeedMultiplier; 


	
};
