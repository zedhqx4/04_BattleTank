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
	Locked,
	OutOfAmmo
};

// Fordward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;


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

	UFUNCTION(BlueprintCallable, Category = "Setup") 	// To be able to call as a propierty from components within BluePrint Editor
	void Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelTrackToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;


protected:
	UPROPERTY(BluePrintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;
	// EFiringState Is the class
	// FiringState IS our variable
	// Initializes to "EFiringState::Reloading"

private:
		// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	//void LaunchProjectile(float Speed);
	void MoveBarrelTowards(FVector AimDirection);
	// void MoveTurretTowards(FVector AimDirection);

	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	//UStaticMeshComponent* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		// UClass* ProjectileBlueprint; /// This let us pick a blueprint in the Tank BLueprint. Danger of crash
		TSubclassOf<AProjectile> ProjectileBlueprint; // Make forward declaration up this file

	UPROPERTY(EditDefaultsOnly, Category = "Firing") // To edit a parameter in the (default)right menu
		float LaunchSpeed = 4000;
		
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;
		
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 RoundsLeft = 3;

	double LastFireTime = 0;

	FVector AimDirection;

	
	
};
