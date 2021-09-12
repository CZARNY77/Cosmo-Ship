// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonus_Gun.generated.h"

UCLASS()
class SHIP_API ABonus_Gun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonus_Gun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FQuat QuatRotation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Component")
	class USphereComponent* MyCollision;

	UPROPERTY(EditAnywhere, Category = "Component")
	class UStaticMeshComponent* MyMesh;

	float SphereRadius;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
