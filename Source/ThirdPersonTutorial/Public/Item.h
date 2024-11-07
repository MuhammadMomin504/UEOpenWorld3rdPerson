// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class THIRDPERSONTUTORIAL_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void DebugCode(float DeltaTime);
	virtual void SetLocationOffset(float DeltaTime);
	virtual void RotateObject(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	float TransformSin(float value);
	
	UFUNCTION(BlueprintPure)
	float TransformCos(float value);

	template<typename T>
	T Avg(T First, T Second);

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Sine Parameters")
	float runningTime = 0.f;
	UPROPERTY(EditAnywhere, Category = "Sine Parameters")
	float amplitude = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Sine Parameters")
	float timeConstant = 5.f;

	UPROPERTY(VisibleAnywhere)
	FVector currentPosition = FVector(0, 0, 0);
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* itemMesh;
	
};

template <typename T>
T AItem::Avg(T First, T Second)
{
	return (First + Second) / 2;
}
