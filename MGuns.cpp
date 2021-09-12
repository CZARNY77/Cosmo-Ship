// Fill out your copyright notice in the Description page of Project Settings.


#include "MGuns.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Asteroids.h"
#include "Bonus_Gun.h"
#include "TestActorSpawn.h"
#include "TimerManager.h"

// Sets default values
AMGuns::AMGuns()
{
 	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");
	SetRootComponent(BulletMesh);

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BulletMovement");
	BulletMovement->InitialSpeed = 30000.f;
	BulletMovement->MaxSpeed = 30000.f;

	OnActorHit.AddDynamic(this, &AMGuns::OnBulletHit);
}

// Called when the game starts or when spawned
void AMGuns::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AMGuns::DestroyFunction, 2.0f, true, 5.0f);

}

// Called every frame
void AMGuns::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMGuns::OnBulletHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trafilem!!")));
	if (AAsteroids* Asteroid = Cast<AAsteroids>(OtherActor)) {
		Asteroid->hp--;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("HP Asteroid: %i"), Asteroid->hp));
		if (Asteroid->hp <= 0) {

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.bNoFail = true;
			SpawnParams.Owner = Asteroid;

			FTransform AsteroidTransform;
			AsteroidTransform.SetLocation(Asteroid->AsteroidMesh->GetForwardVector() * 10000.f + Asteroid->AsteroidMesh->GetComponentLocation());
			AsteroidTransform.SetRotation(Asteroid->AsteroidMesh->GetComponentRotation().Quaternion());
			AsteroidTransform.SetScale3D(FVector(1.f));

			GetWorld()->SpawnActor<AAsteroids>(AsteroidsClass, AsteroidTransform, SpawnParams);
			
			FTransform BonusTransform;
			BonusTransform.SetLocation(Asteroid->AsteroidMesh->GetForwardVector() + Asteroid->AsteroidMesh->GetComponentLocation());
			BonusTransform.SetScale3D(FVector(1.f));

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Vector: %s"), *Asteroid->AsteroidMesh->GetForwardVector().ToString()));

			GetWorld()->SpawnActor<ABonus_Gun>(BonusClass, BonusTransform, SpawnParams);

			Asteroid->Destroy();
		}
		Destroy();
	}
	else
	{
		Destroy();
	}
}

void AMGuns::DestroyFunction()
{
	Destroy();
}

