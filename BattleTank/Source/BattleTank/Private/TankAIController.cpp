// Fill out your copyright notice in the Description page of Project Settings.

#
#include "BattleTank.h"
#include "Tank.h" // moved from header file
#include "Public/TankAIController.h"
// Dependes on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	/*
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *(ControlledTank->GetName()));
	}
	
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController cant find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController %s found player: %s"), *(ControlledTank->GetName()),*(PlayerTank->GetName()));
	}
	*/
}

/*
ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}*/

/*ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)	{	return nullptr;	}
	return Cast<ATank>(PlayerPawn);
}*/

void ATankAIController::Tick(float DeltaTime)
{
	// Super
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	// if (GetPlayerTank())
	if (PlayerTank)
	{
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check radius is in cm

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		ControlledTank->Fire(); // TODO limit firing rate
	}
}