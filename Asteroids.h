// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroids.generated.h"

UCLASS()
class SHIP_API AAsteroids : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroids();

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* AsteroidMesh;

	int hp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Angle;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Scale;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Radius_X;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Radius_Y;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Radius_Z;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	int MoveDirection_X;
	UPROPERTY(EditAnywhere, Category = "Movement")
	int MoveDirection_Y;
	UPROPERTY(EditAnywhere, Category = "Movement")
	int MoveDirection_Z;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float PitchValue;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float YawValue;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RollValue;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
