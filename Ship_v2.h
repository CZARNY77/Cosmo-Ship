// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ship_v2.generated.h"

UCLASS()
class SHIP_API AShip_v2 : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* PlaneMesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BoardMesh;

	UPROPERTY(EditAnywhere, Category = "Guns")
	class UStaticMeshComponent* Gun_P;

	UPROPERTY(EditAnywhere, Category = "Guns")
	class UStaticMeshComponent* Gun_P2;

	UPROPERTY(EditAnywhere, Category = "Guns")
	class UStaticMeshComponent* Gun_L;

	UPROPERTY(EditAnywhere, Category = "Guns")
	class UStaticMeshComponent* Gun_L2;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<class AMGuns> BulletClass;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera_2;


public:

	AShip_v2();

	bool Bonus_G;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void ThrustInput(float Val);
	void MoveUpInput(float Val);
	void MoveRightInput(float Val);
	void TurnRate(float Val);
	void MoveRight(float Val);
	void UpDown(float Val);
	void Stop();
	void Shoot();
	void CameraChange();

	virtual void BeginPlay() override;


private:

	UPROPERTY(Category = Plane, EditAnywhere)
	float Acceleration;
	UPROPERTY(Category = Plane, EditAnywhere)
	float TurnSpeed;
	UPROPERTY(Category = Pitch, EditAnywhere)
	float MaxSpeed;
	UPROPERTY(Category = Yaw, EditAnywhere)
	float MinSpeed;

	float CurrentForwardSpeed;
	float CurrentUpSpeed;
	float CurrentRightSpeed;
	float CurrentYawSpeed;
	float CurrentPitchSpeed;
	float CurrentRollSpeed;

	bool CamChange = false;
	int hp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	FORCEINLINE class UStaticMeshComponent* GetPlaneMesh() const { return PlaneMesh; }
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }

	void BonusEnd();
	FTimerHandle MemberTimerHandle;
};
