// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	
	virtual void BeginPlay() override;

	ATank* GetControlledTank() const;
	
	ATank* GetPlayerTank() const;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Start the tank moving the barrel so that a shot would it where
	// the crosshair intersects the world
	void AimTowardsCrosshair() const;

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.3333333;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;

};
