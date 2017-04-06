// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h" // moved from the header file tank.h
// #include "TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as added at construction
	// THis is what creates the component within BLUEPRINTs
	// TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component")); // This creates the Inherited "TankAimingComponent" in the BP editor
		
}

//void ATank::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
/*void ATank::initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetCanonReference(TurretToSet,BarrelToSet);
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}*/

/*void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetCanonReference(TurretToSet);
}
*/

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP Begin Play to run!
	
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

// Called to bind functionality to input
/*void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	
	if (isReloaded) // && = "and" (was removed "if (barrel && isReloaded)"), || = "or"
	{
		// Spawn the projectile at the socket location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),//#Include TankBarrel.h
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}