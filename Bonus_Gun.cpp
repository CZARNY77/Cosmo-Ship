// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus_Gun.h"
#include "Components/SphereComponent.h"
#include "Ship_v2.h"
#include "TimerManager.h"

// Sets default values
ABonus_Gun::ABonus_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	//RootComponent = MyMesh;
	SetRootComponent(MyMesh);
	//MyMesh->SetupAttachment(RootComponent);

	SphereRadius = 300.f;

	MyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("MySphereComponent"));
	MyCollision->InitSphereRadius(SphereRadius);
	MyCollision->SetCollisionProfileName("Trigger");
	//RootComponent = MyCollision;
	//MyCollision->SetupAttachment(RootComponent);

	MyCollision->OnComponentBeginOverlap.AddDynamic(this, &ABonus_Gun::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ABonus_Gun::BeginPlay()
{
	Super::BeginPlay();
	QuatRotation = FQuat(FRotator(0, 1, 0));
}

// Called every frame
void ABonus_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//MyMesh->SetRelativeLocation(FVector(0, 0, 0));
	//MyCollision->SetRelativeLocation(FVector(0, 0, 0));
	AddActorLocalRotation(QuatRotation);
}

void ABonus_Gun::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AShip_v2* player = Cast<AShip_v2>(OtherActor)) {
		player->Bonus_G = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Bonus!!!")));
		GetWorldTimerManager().SetTimer(player->MemberTimerHandle, player, &AShip_v2::BonusEnd, 15.f, false, 15.f);
		Destroy();
	}

}

