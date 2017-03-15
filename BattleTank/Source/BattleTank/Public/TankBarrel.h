// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
//UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision")) Hides collision in details panel of component
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSecond);

private:

	UPROPERTY(EditAnywhere, Category = setup)
		float MaxDegreesPerSecond = 20; // Sensible default

	UPROPERTY(EditAnywhere, Category = setup)
		float MaxElevationDegrees = 0; 
	
	UPROPERTY(EditAnywhere, Category = setup)
		float MinElevationDegreesd = 0;
};