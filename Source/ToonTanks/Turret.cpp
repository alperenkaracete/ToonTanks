// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Turret.h"

ATurret::ATurret()
{
    
}

void ATurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (Tank){

        
        if (IsInRange()){
            RotateTurret(Tank->GetActorLocation());
            
            
        }
    }

}

void ATurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATurret::BeginPlay()
{

    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    
    GetWorldTimerManager().SetTimer(FireRateTimerHandle,this,&ATurret::CheckFireCondition,FireRate,true);
}

void ATurret::RotateTurret(FVector TargetLocation)
{
    Super::RotateTurret(TargetLocation);

}

void ATurret::CheckFireCondition()
{
    if (Tank){

        
        if (IsInRange()){
            Fire();
            
        }
    }
}

bool ATurret::IsInRange(){

    float Distance = FVector::Dist(Tank->GetActorLocation(),GetActorLocation());
    if (Distance <= TurretRange){

        return true;
    }
    else 
        return false;
}
