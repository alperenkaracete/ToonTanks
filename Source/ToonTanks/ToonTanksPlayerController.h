// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
		void SetPlayerEnabledState (bool bPlayerEnabledState);
		class UEnhancedInputLocalPlayerSubsystem* Subsystem;
		APlayerController* PlayerController;
		class UEnhancedInputLocalPlayerSubsystem* GetSubsystem ();
		APlayerController* GetPlayerController();
		class AToonTanksGameMode* ToonTanksGameMode;

	private:
	
	protected:
		virtual void BeginPlay() override;
};
