// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");

	CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraSpringArm");
	CameraArm->SetupAttachment(StaticMesh);
	CameraArm->TargetArmLength = 500.f;

	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	Camera->SetupAttachment(CameraArm);

	SetRootComponent(StaticMesh);

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;


	RotationValue = 10.f;

	Acceleration = 500.f;
	TurnSpeed = 50.f;
	MaxSpeed = 4000.f;
	MinSpeed = 500.f;
	CurrentForwardSpeed = 500.f;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void AMyPlayer::MoveForward(float Amount)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Predkosc: %f"), CurrentForwardSpeed));
	//CurrentForwardSpeed += Amount * 100.f * GetWorld()->GetDeltaSeconds();

	bool bHasInput = !FMath::IsNearlyEqual(Amount, 0.f);
	float CurrentAcc = bHasInput ? (Amount * Acceleration) : (-0.5f * Acceleration);
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
}

void AMyPlayer::MoveRight(float Amount)
{
	
	//FloatingPawnMovement->AddInputVector(GetActorRightVector() * Amount);
}

void AMyPlayer::TurnRate(float Amount)
{
	float TargetYawSpeed = (Amount * TurnSpeed);
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
	const bool bIsTurning = FMath::Abs(Amount) > 0.2f;
	float TargetRollSpeed = bIsTurning ? (CurrentYawSpeed * 0.5f) : (GetActorRotation().Roll * -2.f);
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	//FRotator NewRotation = GetActorRotation().Add(RotationValue*Amount, RotationValue * Amount, RotationValue*Amount);
	//SetActorRotation(NewRotation);
}

void AMyPlayer::UpDown(float Amount)
{
	float TargetPitchSpeed = (Amount * TurnSpeed * -1.f);
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("odchylenie: %f, %f, %f"), TargetPitchSpeed, CurrentPitchSpeed, Amount));
}

void AMyPlayer::Turn(float Amount)
{
	//AddControllerYawInput(Amount);
}

void AMyPlayer::LookUp(float Amount)
{
	//AddControllerPitchInput(Amount);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("odchylenie: %f, %f, %f"), TargetPitchSpeed, CurrentPitchSpeed, Amount));
}

void AMyPlayer::Shoot()
{
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaTime, 0.f, 0.f);

	AddActorLocalOffset(LocalMove, true);

	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaTime;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaTime;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaTime;

	AddActorLocalRotation(DeltaRotation);

	Super::Tick(DeltaTime);

}

void AMyPlayer::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyPlayer::TurnRate);
	PlayerInputComponent->BindAxis("UpDown", this, &AMyPlayer::UpDown);
	PlayerInputComponent->BindAxis("Turn", this, &AMyPlayer::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyPlayer::LookUp);

}

