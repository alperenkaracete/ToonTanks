// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	virtual void HandleDestruction();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float speed = 400;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void RotateTurret(FVector TargetLocation);
	virtual void Fire();
	virtual void ActorDied();


private:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Components",meta = (AllowPrivateAccess = "true"));
	class UCapsuleComponent* CapsuleComp;	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Components",meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Projectile",meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditDefaultsOnly,Category = "Projectile");
	TSubclassOf<class AProjectile> ProjectileClass;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
