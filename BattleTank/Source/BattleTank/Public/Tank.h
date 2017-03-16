// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "TankAimingComponent.h" // not needed here, but in the cpp file
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above this ALWAYS

// Forward declarations
class UTankBarrel;
class UTankAimingComponent; 

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		
		void SetBarrelReference(UTankBarrel* BarrelToSet);
		//void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000; // TODO find sensible default (Sensible starting value of 1000 m/s)

};
