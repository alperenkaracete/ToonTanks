// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h" 
#include "ToonTanksPlayerController.h"
#include "ToonTanksGameMode.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor){

    if (DeadActor == Tank){

        Tank->HandleDestruction();
        if (ToonTanksPlayerController){
            /*Tank->DisableInput(Tank->GetTankPlayerController());
            Tank->GetTankPlayerController()->bShowMouseCursor = false;
            if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Tank->GetTankPlayerController()->GetLocalPlayer())){
                Subsystem->ClearAllMappings();
            }*/
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
    }

    else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor)){

        DestroyedTurret->HandleDestruction();
    }
}

ATank* AToonTanksGameMode::GetTank()
{
    return Tank;
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));
    

    if (ToonTanksPlayerController){

        ToonTanksPlayerController->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,&AToonTanksPlayerController::SetPlayerEnabledState,true);
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,PlayerEnableTimerDelegate,StartDelay,false);
    }
}
