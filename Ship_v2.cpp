// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship_v2.h"
#include "MGuns.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "DrawDebugHelpers.h"

// Sets default values
AShip_v2::AShip_v2()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Ships_models/StarSparrow01.StarSparrow01"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh0"));
	PlaneMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	RootComponent = PlaneMesh;

	BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Board0"));
	BoardMesh->SetupAttachment(RootComponent);

	Gun_P = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun1"));
	Gun_P->SetupAttachment(RootComponent);

	Gun_P2 = CreateDefaultSubobject<UStaticMeshComponent>("Gun_P2");
	Gun_P2->SetupAttachment(RootComponent);

	Gun_L = CreateDefaultSubobject<UStaticMeshComponent>("Gun_L");
	Gun_L->SetupAttachment(RootComponent);

	Gun_L2 = CreateDefaultSubobject<UStaticMeshComponent>("Gun_L2");
	Gun_L2->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);	
	SpringArm->TargetArmLength = 0.0f; 
	SpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 15.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	Camera_2 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera1"));
	Camera_2->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera_2->bUsePawnControlRotation = false;

	Acceleration = 200.f;
	TurnSpeed = 100.f;
	MaxSpeed = 1000.f;
	MinSpeed = -200.f;
	CurrentForwardSpeed = 100.f;
	CurrentUpSpeed = 0.f;
	CurrentRightSpeed = 0.f;
	hp = 5;
	Bonus_G = false;
}

void AShip_v2::ThrustInput(float Val)
{
	//bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	bool bHasInput = Val > 0.2f;
	float CurrentAcc = bHasInput ? (Val * Acceleration) : (Val * 2 * Acceleration);
	MaxSpeed = bHasInput ? 5000.f : 1000.f;
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Prêdkosc: %f, %f, %f"), CurrentAcc, CurrentForwardSpeed, Val));
}

void AShip_v2::MoveUpInput(float Val)
{
	float TargetPitchSpeed = (Val * TurnSpeed * -1.f * (CurrentForwardSpeed/ MaxSpeed));
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Obrocenie: %f, %f, %f"), TargetPitchSpeed, CurrentPitchSpeed, Val));
}

void AShip_v2::MoveRightInput(float Val)
{
	float TargetYawSpeed = (Val * TurnSpeed * (CurrentForwardSpeed/ MaxSpeed));
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	//const bool bIsTurning = FMath::Abs(Val) > 0.2f;
	//float TargetRollSpeed = bIsTurning ? (CurrentYawSpeed * 0.5f) : (GetActorRotation().Roll * -2.f);
	float TargetRollSpeed = (Val * TurnSpeed * (CurrentForwardSpeed / MaxSpeed));
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void AShip_v2::TurnRate(float Val)
{
	float TargetRollSpeed = (Val * TurnSpeed * 10.f);
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Obrocenie: %f, %f, %f"), TargetRollSpeed, CurrentRollSpeed, Val));
}

void AShip_v2::MoveRight(float Val)
{
	float NewRightSpeed = (Val * TurnSpeed * 10);
	CurrentRightSpeed = FMath::FInterpTo(CurrentRightSpeed, NewRightSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void AShip_v2::UpDown(float Val)
{
	
	float NewUpSpeed = (Val * TurnSpeed * 10);
	CurrentUpSpeed = FMath::FInterpTo(CurrentUpSpeed, NewUpSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Wzniesienie: %f, %f, %f"), NewUpSpeed, CurrentUpSpeed, Val));
}

void AShip_v2::Stop()
{
	bool bDirection = CurrentForwardSpeed > 0.2;
	float CurrentAcc = bDirection ? (-5 * Acceleration): (5 * Acceleration);
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	CurrentForwardSpeed = bDirection ? FMath::Clamp(NewForwardSpeed, 0.f, MaxSpeed) : FMath::Clamp(NewForwardSpeed, MinSpeed, 0.f);
}

void AShip_v2::Shoot()
{
	if (BulletClass) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.bNoFail = true;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;

		FTransform BulletSpawnTransform_L;
		FTransform BulletSpawnTransform_P;
		BulletSpawnTransform_L.SetLocation(Gun_L->GetForwardVector() * 200.f + Gun_L->GetComponentLocation());
		BulletSpawnTransform_L.SetRotation(Gun_L->GetComponentRotation().Quaternion());
		BulletSpawnTransform_L.SetScale3D(FVector(1.f));

		BulletSpawnTransform_P.SetLocation(Gun_P->GetForwardVector() * 200.f + Gun_P->GetComponentLocation());
		BulletSpawnTransform_P.SetRotation(Gun_P->GetComponentRotation().Quaternion());
		BulletSpawnTransform_P.SetScale3D(FVector(1.f));

		GetWorld()->SpawnActor<AMGuns>(BulletClass, BulletSpawnTransform_L, SpawnParams);
		GetWorld()->SpawnActor<AMGuns>(BulletClass, BulletSpawnTransform_P, SpawnParams);

		if (Bonus_G) {
			FTransform BulletSpawnTransform_L2;
			FTransform BulletSpawnTransform_P2;
			BulletSpawnTransform_L2.SetLocation(Gun_L2->GetForwardVector() * 500.f + Gun_L2->GetComponentLocation());
			BulletSpawnTransform_L2.SetRotation(Gun_L2->GetComponentRotation().Quaternion());
			BulletSpawnTransform_L2.SetScale3D(FVector(1.f));

			BulletSpawnTransform_P2.SetLocation(Gun_P2->GetForwardVector() * 500.f + Gun_P2->GetComponentLocation());
			BulletSpawnTransform_P2.SetRotation(Gun_P2->GetComponentRotation().Quaternion());
			BulletSpawnTransform_P2.SetScale3D(FVector(1.f));

			GetWorld()->SpawnActor<AMGuns>(BulletClass, BulletSpawnTransform_L2, SpawnParams);
			GetWorld()->SpawnActor<AMGuns>(BulletClass, BulletSpawnTransform_P2, SpawnParams);
		}

	}
}

void AShip_v2::CameraChange()
{
	if (CamChange) {
		CamChange = false;
		SpringArm->TargetArmLength = 0.0f;
		
		Camera->Activate();
		Camera_2->Deactivate();
		/*FVector CurrentLocation = Camera->GetComponentLocation();
		CurrentLocation.X = -33.f;
		CurrentLocation.Y = 0.;
		CurrentLocation.Z = -200.f;
		SetActorLocation(CurrentLocation);*/
	}
	else if (!CamChange) {
		CamChange = true;
		SpringArm->TargetArmLength = 1500.0f;
		Camera_2->Activate();
		Camera->Deactivate();

	}
	

}

void AShip_v2::BonusEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Koenic bonusu")));
	Bonus_G = false;
}

void AShip_v2::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShip_v2::Tick(float DeltaTime)
{
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaTime, CurrentRightSpeed * DeltaTime, CurrentUpSpeed * DeltaTime);

	AddActorLocalOffset(LocalMove, true);

	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaTime;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaTime;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaTime;

	AddActorLocalRotation(DeltaRotation);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Bonus: %i"), Bonus_G));

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP: %i"), hp));
	Super::Tick(DeltaTime);
}

void AShip_v2::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	Other->Destroy();
	//CurrentForwardSpeed /= 2;

	FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Kabuuum")));
}

// Called to bind functionality to input
void AShip_v2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Stop", IE_Repeat, this, &AShip_v2::Stop);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShip_v2::Shoot);
	PlayerInputComponent->BindAction("CameraChange", IE_Pressed, this, &AShip_v2::CameraChange);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShip_v2::ThrustInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AShip_v2::MoveUpInput);
	PlayerInputComponent->BindAxis("Turn", this, &AShip_v2::MoveRightInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AShip_v2::TurnRate);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShip_v2::MoveRight);
	PlayerInputComponent->BindAxis("UpDown", this, &AShip_v2::UpDown);

}

