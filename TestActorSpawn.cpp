// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActorSpawn.h"
#include "Components/SphereComponent.h"
#include "Ship_v2.h"
#include "TimerManager.h"

// Sets default values
ATestActorSpawn::ATestActorSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TestMesh"));
	//RootComponent = TestMesh;
	//TestMesh->SetupAttachment(RootComponent);
	SetRootComponent(TestMesh);

	SphereRadius = 100.f;

	MyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("MySphereComponent"));
	MyCollision->InitSphereRadius(SphereRadius);
	MyCollision->SetCollisionProfileName("Trigger");
	//RootComponent = MyCollision;
	//MyCollision->SetupAttachment(RootComponent);
	//SetRootComponent(MyCollision);

	MyCollision->OnComponentBeginOverlap.AddDynamic(this, &ATestActorSpawn::OnOverlapBegin);
	
}

// Called when the game starts or when spawned
void ATestActorSpawn::BeginPlay()
{
	Super::BeginPlay();
	QuatRotation = FQuat(FRotator(0, 1, 0));
}

// Called every frame
void ATestActorSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(QuatRotation);
	//MyCollision->SetRelativeLocation(FVector(0, 0, 40));
	//TestMesh->SetRelativeLocation(FVector(0, 0, 0));
}

void ATestActorSpawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Overlap!!!")));
	if (AShip_v2* player = Cast<AShip_v2>(OtherActor)) {
		player->Bonus_G = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Bonus!!!")));
		GetWorldTimerManager().SetTimer(player->MemberTimerHandle, player, &AShip_v2::BonusEnd, 15.f, false, 15.f);
		Destroy();
	}

}

