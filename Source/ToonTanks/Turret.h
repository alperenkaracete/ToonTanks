// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Engine/TimerHandle.h"
#include "Turret.generated.h"

/**
 * 
 */

class ATank;

UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

	public:
		ATurret();
		virtual void Tick(float DeltaTime) override;
		virtual void HandleDestruction() override;
		

	protected:
		UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Turret", meta = (AllowPrivateAccess = "true"))
		int TurretRange = 1000;
		virtual void BeginPlay() override;	
		virtual void RotateTurret(FVector TargetLocation) override;
	
	private:
		ATank* Tank;

		FTimerHandle FireRateTimerHandle;
		float FireRate = 2.f;
		void CheckFireCondition();
		bool IsInRange();
};
