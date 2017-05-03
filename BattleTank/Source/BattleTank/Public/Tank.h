// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "TankAimingComponent.h" // not needed here, but in the cpp file
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above this ALWAYS

// Forward declarations
//class UTankBarrel;
//class UTankTurret;
// class UTankAimingComponent;
// class UTankMovementComponent;
//class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// called by the engine when actor damage is deal
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Returns current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	/*
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);
		//void SetBarrelReference(UStaticMeshComponent* BarrelToSet);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);
	*/
	
	

	//UFUNCTION(BlueprintCallable)
		//void Fire();

//protected:
	// protected pointers to use in BluePrint
	//UPROPERTY(BlueprintReadOnly)
	// UTankAimingComponent* TankAimingComponent = nullptr;
	
	// UPROPERTY(BlueprintReadOnly) //Add this to be able to add as node within Blueprint
	// UTankMovementComponent* TankMovementComponent = nullptr;

	


private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY (EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;

};






	// Called when the game starts or when spawned
	// virtual void BeginPlay() override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/*UPROPERTY(EditDefaultsOnly, Category = "Setup")
		// UClass* ProjectileBlueprint; /// This let us pick a blueprint in the Tank BLueprint. Danger of crash
		TSubclassOf<AProjectile> ProjectileBlueprint; // Make forward declaration up this file

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	// TODO remove once firing is moved to aiming component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000; // TODO find sensible default (Sensible starting value of 1000 m/s)
		

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; // Not needed anymore
	
		
	double LastFireTime = 0;
	*/

