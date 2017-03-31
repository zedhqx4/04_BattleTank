// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Fordward Declaration
class UTankBarrel;
class UTankTurret;



/**
*  Hold Barrel's properties and elevate method
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	


	//void SetCanonReference(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);
	//void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);


	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelTrackToSet);


protected:
	UPROPERTY(BluePrintReadOnly, Category = "State")
		// EFiringState Is the class
		// FiringState IS our variable
		// Initializes to "EFiringState::Reloading"
		EFiringState FiringState = EFiringState::Reloading;

private:
		// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	//UStaticMeshComponent* Barrel = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	UTankTurret* Turret = nullptr;
	//UStaticMeshComponent* Barrel = nullptr;

	void MoveTurretTowards(FVector AimDirection);

	
};
