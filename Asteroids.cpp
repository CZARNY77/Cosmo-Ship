// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroids.h"

// Sets default values
AAsteroids::AAsteroids()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AsteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>("AsteroidMesh");
	SetRootComponent(AsteroidMesh);
	

	Angle = 0.f;
}

// Called when the game starts or when spawned
void AAsteroids::BeginPlay()
{
	Super::BeginPlay();
	Scale = FMath::FRandRange(1.f, 10.f);
	hp = Scale;
	SetActorScale3D(FVector(Scale, Scale, Scale));

	Radius_X = FMath::RandRange(-15, 15) * 1000;
	Radius_Y = FMath::RandRange(-15, 15) * 1000;
	Radius_Z = FMath::RandRange(-15, 15) * 1000;

	Speed = FMath::FRandRange(0.1f, 0.5f);

	MoveDirection_X = FMath::RandRange(-1, 1);
	MoveDirection_Y = FMath::RandRange(-1, 1);
	MoveDirection_Z = FMath::RandRange(-1, 1);

	PitchValue = FMath::RandRange(-3, 3);
	YawValue = FMath::RandRange(-3, 3);
	RollValue = FMath::RandRange(-3, 3);

}

// Called every frame
void AAsteroids::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Radius = FVector(Radius_X, Radius_Y, Radius_Y);
	Angle += Speed;

	if (Angle > 360.f)	Angle = 1.f;

	FVector RotateValue = Radius.RotateAngleAxis(Angle, FVector(MoveDirection_X, 0, MoveDirection_Z));
	FQuat QuatRotation = FQuat(FRotator(PitchValue / Scale, YawValue / Scale, RollValue / Scale));
	SetActorLocation(RotateValue);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

