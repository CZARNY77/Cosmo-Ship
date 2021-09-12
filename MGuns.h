// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGuns.generated.h"

UCLASS()
class SHIP_API AMGuns : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMGuns();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Component")
		UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditAnywhere, Category = "Component")
		class UProjectileMovementComponent* BulletMovement;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class AAsteroids> AsteroidsClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class ABonus_Gun> BonusClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBulletHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void DestroyFunction();

	FTimerHandle MemberTimerHandle;
};
