// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

// Forward declaration
// class ATank; // somewhere down here we have ATank class
class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	//UFUNCTION(BlueprintCallable, Category = "Setup") //Add this to be able to add as node within Blueprint
	//ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef); // EVENTNAME(Argument)

private:
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Start the tank moving the barrel so that a shot would it where
	// the crosshair intersects the world
	void AimTowardsCrosshair() const;

	/// Return an OUT parameter, true if hit landscape
	// Returns bool
	// Called GetSightRayHitLocation
	// Mutates/changes an FVector
	// & Parses a REFERENCE to an FVector
	// FVector is gonna be called HitLocation
	// Method is gonna be constant, wont change any member variables
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3333333;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000; // LineTrace distance 10KM (10,000M, 1,000,000 cm)
	
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
	
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
		
	


};
