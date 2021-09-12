// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gen.generated.h"

UCLASS()
class SHIP_API AGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMeshComponent* GenMesh;

	UPROPERTY(EditAnywhere, Category = "AsteroidSpawn")
	TSubclassOf<class AAsteroids> AsteroidsClass;

	UPROPERTY(EditAnywhere, Category = "AsteroidSpawn")
	float Radius;
	
	UPROPERTY(EditAnywhere, Category = "AsteroidSpawn")
	int Number;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
