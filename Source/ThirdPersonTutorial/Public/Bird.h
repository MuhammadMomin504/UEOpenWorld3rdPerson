// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"
	
class UCapsuleComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class THIRDPERSONTUTORIAL_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void RotateMeshX(float axisValue);
	
	float pitchRotationSpeed = 100.0f;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetSpeedMultiplier() const { return speedMultiplier; }

	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool GetMovingUp() { return isMovingUp; }

	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool GetMovingDown() { return isMovingDown; }
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float value);
	void Turn(float value);
	void LookUp(float value);
	void TurnUsingKeys(float value);
	float MoveTowards(float current, float target, float maxDelta);

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	// UCameraComponent* cameraBoom;

private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* capsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* birdMesh;

	UPROPERTY(VisibleAnywhere)
	bool shouldResetRotation = false;

	UPROPERTY(VisibleAnywhere)
	bool isGlideState = false;

	UPROPERTY(VisibleAnywhere)
	bool isMovingUp = false;

	UPROPERTY(VisibleAnywhere)
	bool isMovingDown = false;

	UPROPERTY(VisibleAnywhere)
	float speedMultiplier = 1.0f;

	float timeElapsed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float sineAmplitude = 30.f;
	
	UPROPERTY(EditAnywhere, Category = "Stats")
	float sineFrequency = 1.f;
	

};
