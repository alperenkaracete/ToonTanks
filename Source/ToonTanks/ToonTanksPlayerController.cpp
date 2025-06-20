// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksGameMode.h"
#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabledState)
{

    if (bPlayerEnabledState){

        GetPawn()->EnableInput(this);
        ToonTanksGameMode->GetTank()->SetTankMappingContext();
    }
    else{

        GetPawn()->DisableInput(this);

        if(Subsystem){
            Subsystem->ClearAllMappings();
        }
    }
    bShowMouseCursor = bPlayerEnabledState;

}

UEnhancedInputLocalPlayerSubsystem* AToonTanksPlayerController::GetSubsystem()
{
    return Subsystem;
}

APlayerController *AToonTanksPlayerController::GetPlayerController()
{
    return PlayerController;
}

void AToonTanksPlayerController::BeginPlay(){

    Super::BeginPlay();
    PlayerController = Cast<APlayerController>(GetPawn()->GetController());
    Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));

}