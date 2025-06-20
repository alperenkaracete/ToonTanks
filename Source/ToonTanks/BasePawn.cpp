// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include "BasePawn.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::RotateTurret(FVector TargetLocation){

	FVector ToTarget = TargetLocation - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator (0.f,ToTarget.Rotation().Yaw,0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(),LookAtRotation,GetWorld()->GetDeltaSeconds(),15));
}

void ABasePawn::Fire()
{
	
	//DrawDebugSphere(GetWorld(),ProjectileSpawnPoint->GetComponentLocation(),25,12,FColor::Red,false,10);
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,ProjectileSpawnPoint->GetComponentLocation(),ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{

}

void ABasePawn::ActorDied()
{
	
}
