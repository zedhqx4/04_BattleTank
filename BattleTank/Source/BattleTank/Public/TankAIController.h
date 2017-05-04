// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// #include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close can the AI tank get
	//Must be in protected since BP is a child class from c++ class
	UPROPERTY(EditDefaultsOnly, Category = "Setup") // Consider 
	float AcceptanceRadius = 80000;

private:
	
	virtual void BeginPlay() override;

	//ATank* GetPlayerTank() const;

	virtual void SetPawn(APawn* InPawn) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Delegate method to work from the FTankDelegate in Tank.h
	UFUNCTION()
		void OnPossedTankDeath();
};

