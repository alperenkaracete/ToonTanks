// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	public:
		ATank();
		// Called every frame
		virtual void Tick(float DeltaTime) override;
		virtual void HandleDestruction();

		class AToonTanksPlayerController* GetToonTanksPlayerController();
		class APlayerController* GetTankPlayerController();
		void SetTankMappingContext();

	protected:
		virtual void BeginPlay() override;	
		class AToonTanksPlayerController* ToonTanksPlayerController;
		APlayerController* PlayerController;
		virtual void RotateTurret(FVector TargetLocation) override;

	private:
		UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;

		UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

		UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* TankMappingContext;
		
		UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

		UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
		class UInputAction* TurnAction;

		UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;		

		UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Input", meta = (AllowPrivateAccess = "true"))
		class UInputAction* FireAction;	

		UPROPERTY(EditAnywhere,Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float TurnSpeed = 150;

		void Move(const FInputActionValue& Value);
		void Turn(const FInputActionValue& Value);
		void Look(const FInputActionValue& Value);
		void TankFire(const FInputActionValue& Value);
		void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
};
