// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

//Edit this to add a description to a component within the BluePrint
/**
 * Responsible for driving the tank tracks
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) // Needed to be able to add as a component within BluePrintEditor
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
		
public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	// This is needed to be able to call and add within BluePrint "Intended Move Forward"
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendedMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendedTurnRight(float Throw);
	
	// TODO check best protection
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	
};
