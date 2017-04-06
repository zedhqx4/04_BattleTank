// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


void UTankAimingComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // Should this tick? NO

	// ...
}

void  UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { UE_LOG(LogTemp, Warning, TEXT("Works till here !Barrel"));  return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // In the engine create a socket in a mesh, if it fails uses location of the barrel (element
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);	
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto OurTankName = GetOwner()->GetName();
		//auto BarrelLocation = Barrel->GetComponentLocation().ToString();
		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming At: %s"), *OurTankName, *HitLocation.ToString())
		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at: %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation)
		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at: %s"), *OurTankName, *AimDirection.ToString());
		//%f parse float value %s string value
		MoveBarrelTowards(AimDirection);
		
		
	}
	else
	{
		if (!ensure(Turret)) { return; }
		/*auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT(" %f: No aim solve found"), Time);
		*/
	}
	// if no solution found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// if (!ensure(Barrel && Turret)) { return; }
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	// Work-out difference between current barrel roation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	// TankBarrel.cpp method line 11
	Barrel->Elevate(DeltaRotator.Pitch); // TODO remove magic number
	Turret->Rotate(DeltaRotator.Yaw);
}