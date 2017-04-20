// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *  TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets a throttle between -1 and 1
	UFUNCTION(BLueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// Max force per track, in newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000; // Assume 40 tonne tank, and 1g acceleration (40K Kg Tank mass, Force = massXacceleration, 10ms^-2 (1g) acceleration)

private:
	UTankTrack();

	/*virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;*/

	void ApplySidewaysForce();

	virtual void BeginPlay() override;

	// This is to get OnComponentHit Behaviour
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void DriveTrack();
	
	float CurrentThrottle = 0;
};
