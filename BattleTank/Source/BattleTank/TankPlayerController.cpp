// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
// #include "Public/Tank.h"
#include "TankPlayerController.h"

// Tick
void ATankPlayerController::Tick(float DeltaTime)
{
	// Super
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	// UE_LOG(LogTemp, Warning, TEXT("PlayController Ticking"));
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
	
	/*auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"),*(ControlledTank->GetName()));
	}*/
	
}

/*
ATank* ATankPlayerController::GetControlledTank() const
{
	// return Cast<ATank>(GetPawn());
	return GetPawn();
}
*/
void ATankPlayerController::AimTowardsCrosshair() const
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation)) // HAS "side-effect", is going to line trace //parsing Hitlocation as the thing going to be used as the OUT parameter
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
		AimingComponent->AimAt(HitLocation); // call to TANK.h-cpp AimAt()

	}
}

// Get World location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
//	HitLocation = FVector(1.0);
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	// UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	//"De-Project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation,LookDirection)) 
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
		GetLookVectorHitLocation(LookDirection, HitLocation); // LINE-TRACE METHOD CALL // Parse LookDirection // and parse in HitLocation as an OUT parameter
	}
		
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const // LINE-TRACE METHOD
{
	FHitResult HitResult; // FHitResult stores HitResult variable
	auto StartLocation = PlayerCameraManager->GetCameraLocation(); // Need an start location lets call it StartLocation. To get it, get camera location, use PlayerCameraManager and then getcameralocation(), 
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange); // Need an end location lets call it EndLocation. (* is multiplyng not a pointer)
	// If line-trace succeeds
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)  // We need getworld coz thats the context to do the line trace (for accessing object member variables and methods via pointer to object)
		)
	{
		// set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	// set to 0 when hit location doesnt exist
	HitLocation = FVector(0);
	return false; // Line Trace didn't succeed
	
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;//To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
}