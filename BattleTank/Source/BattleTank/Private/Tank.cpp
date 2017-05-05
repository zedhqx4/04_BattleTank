// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
//#include "TankBarrel.h"
// #include "Projectile.h"
// #include "TankAimingComponent.h" // moved from the header file tank.h
// #include "TankMovementComponent.h"
#include "Tank.h"


float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth; // Casting CurrentHealth to a float
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	//BustedTank = CreateDefaultSubobject<UParticleSystemComponent>(FName("Busted Tank"));
	//BustedTank->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//BustedTank->bAutoActivate = false;
	// No need to protect pointers as added at construction
	// THis is what creates the component within BLUEPRINTs
	// TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component")); // This creates the Inherited "TankAimingComponent" in the BP editor
		
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP Begin Play to run!
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount); // Convert float to int
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth); // Clamp damage between 0 and current health (for when more damage than actual health might dealt)
	
	CurrentHealth -= DamageToApply;
		if (CurrentHealth <= 0)
		{
			OnDeath.Broadcast();
			
			//BustedTank->Activate();
			UE_LOG(LogTemp, Warning, TEXT("Tank died"));
		}

	return DamageToApply;
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

// Called to bind functionality to input
/*void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/


/*void ATank::Fire()
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
}*/