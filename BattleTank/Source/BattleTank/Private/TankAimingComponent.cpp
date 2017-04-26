// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
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
	PrimaryComponentTick.bCanEverTick = true; // Should this tick? NO (Now it should so YES, tickcomponent below)

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{

	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	
	
	//UE_LOG(LogTemp, Warning, TEXT("Aiming Comp. Ticking"));
	else if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
	// TODO Handle aiming and locked states
}


int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); // vectors are equal
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
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

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirectionFix)
{
	// if (!ensure(Barrel && Turret)) { return; }
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	// Work-out difference between current barrel roation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirectionFix.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	// TankBarrel.cpp method line 11

	// Always yaw the shortest way
	Barrel->Elevate(DeltaRotator.Pitch); // TODO remove magic number
	if ( FMath::Abs(DeltaRotator.Yaw) < 180) // Takes Absolute value of the YAW and ask if it is less than 180
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else // Avoid going the long-way round
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::Fire()
{
	// bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	//if (isReloaded) // && = "and" (was removed "if (barrel && isReloaded)"), || = "or"
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		// Spawn the projectile at the socket location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),//#Include TankBarrel.h
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

