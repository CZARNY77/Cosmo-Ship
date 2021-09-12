// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPlayer.generated.h"

UCLASS()
class SHIP_API AMyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void TurnRate(float Amount);
	void UpDown(float Amount);
	void Turn(float Amount);
	void LookUp(float Amount);
	void Shoot();

	class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationValue;

	UPROPERTY(Category = Plane, EditAnywhere)
	float Acceleration;

	UPROPERTY(Category = Plane, EditAnywhere)
	float TurnSpeed;

	UPROPERTY(Category = Pitch, EditAnywhere)
	float MaxSpeed;

	UPROPERTY(Category = Yaw, EditAnywhere)
	float MinSpeed;

	float CurrentForwardSpeed;
	float CurrentYawSpeed;
	float CurrentPitchSpeed;
	float CurrentRollSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
