// Fill out your copyright notice in the Description page of Project Settings.


#include "Gen.h"
#include "Asteroids.h"

// Sets default values
AGen::AGen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GenMesh"));
	GenMesh->SetupAttachment(RootComponent);

	Radius = 2000.f;
	Number = 10;

}

// Called when the game starts or when spawned
void AGen::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bNoFail = true;
	SpawnParams.Owner = this;


	for (int i = 0; i < Number; i++) {

		FTransform AsteroidTransform;
		AsteroidTransform.SetLocation(this->GetActorLocation());
		AsteroidTransform.SetRotation(this->GetActorRotation().Quaternion());
		AsteroidTransform.SetScale3D(FVector(1.f));

		GetWorld()->SpawnActor<AAsteroids>(AsteroidsClass, AsteroidTransform, SpawnParams);
	}
}

// Called every frame
void AGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

