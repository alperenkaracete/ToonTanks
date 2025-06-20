// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "ToonTanksPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

ATank::ATank(){

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArmComponent->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
    
    SetTankMappingContext();

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

AToonTanksPlayerController *ATank::GetToonTanksPlayerController()
{
    if (ToonTanksPlayerController)
        return ToonTanksPlayerController;

    else
        return nullptr;    
}

APlayerController *ATank::GetTankPlayerController()
{
    if (PlayerController)
        return PlayerController;
    else    
        return nullptr;
}

void ATank::Move(const FInputActionValue& Value){

    const float DirectionValue = Value.Get<float>();

    if (GetController() && DirectionValue != 0.f){

        FVector Forward = GetActorForwardVector();
        AddMovementInput(Forward , DirectionValue);
    }
}

void ATank::Turn(const FInputActionValue& Value)
{
    const float DirectionValue = Value.Get<float>();

    if (GetController() && DirectionValue != 0.f)
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw = DirectionValue * GetWorld()->GetDeltaSeconds() * TurnSpeed;
        AddActorLocalRotation(NewRotation, true);
    }
}

void ATank::Look(const FInputActionValue &Value)
{
    const FVector2D LookAxisValue = Value.Get<FVector2D>();

    if (GetController()){

        //This lines are for turning tank to left right and turn camera up down.

        //Tank
        /*FRotator NewLookRotation = GetActorRotation();
        NewLookRotation.Yaw = LookAxisValue.X * GetWorld()->GetDeltaSeconds() * TurnSpeed;
        AddActorLocalRotation(NewLookRotation, true);*/

        //Camera
        /*if (SpringArmComponent)
        {
            FRotator NewRotation = SpringArmComponent->GetRelativeRotation();
            NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + LookAxisValue.Y, -80.0f, 10.0f); 
            SpringArmComponent->SetRelativeRotation(NewRotation);
        }*/
        FHitResult HitResult;
        ToonTanksPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResult);
        //DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,25.f,12,FColor::Cyan);
        RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){

    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)){

        EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ATank::Move);
        EnhancedInputComponent->BindAction(TurnAction,ETriggerEvent::Triggered,this,&ATank::Turn);
        EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ATank::Look);
        EnhancedInputComponent->BindAction(FireAction,ETriggerEvent::Triggered,this,&ATank::Fire);
    }
}

void ATank::RotateTurret(FVector TargetLocation){

	Super::RotateTurret(TargetLocation);
}

void ATank::TankFire(const FInputActionValue& Value){

    bool isFire = Value.Get<bool>();

    if (isFire){

        Fire();
    } 
}

void ATank::SetTankMappingContext()
{
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(GetController());
    PlayerController = Cast<APlayerController>(GetController());
	if(ToonTanksPlayerController){

        if(UEnhancedInputLocalPlayerSubsystem* Subsytem = ToonTanksPlayerController->GetSubsystem()){

           Subsytem->AddMappingContext(TankMappingContext, 0);
        }
    }
}
