// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Fordward Declaration
class UTankBarrel;

// Hold Barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	//void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	// TODO add SetTurrentReference

	void AimAt(FVector HitLocation, float LaunchSpeed);

private:
	UTankBarrel* Barrel = nullptr;
	//UStaticMeshComponent* Barrel = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

};