// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"

class UCameraComponent;
class USpringArmComponent;

#include "CameraControllerPawnClass.generated.h"

UCLASS()
class THIRDPERSONTUTORIAL_API ACameraControllerPawnClass : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraControllerPawnClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* cameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* springArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	AActor* targetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FVector cameraOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float smoothSpeed;

	void Turn(float value);
	void LookUp(float value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
