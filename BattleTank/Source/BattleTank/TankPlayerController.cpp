// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"),*(ControlledTank->GetName()));
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() const
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation)) // HAS "side-effect", is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
		GetControlledTank()->AimAt(HitLocation);
		//If it hits the landscape
		// TODO Tell Controlled tank to aim a this point
	}
}


/*
bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	HitLocation = FVector(1.0);
	return false;
}*/

// Get World location of linetrace through crosshai, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
//	HitLocation = FVector(1.0);
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	// UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());
	//"De-Project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation,LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	// Line-trace along that LookDirection, and see what we hit (up to amax range)
	return true;
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

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection *LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line Trace didn't succeed
	
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
}