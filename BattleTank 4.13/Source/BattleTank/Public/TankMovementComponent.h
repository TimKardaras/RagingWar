// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) //allows us to add the component manually
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:

	//initialize must be blueprint callable as it allows the tracks to be set
	UFUNCTION(BluePrintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	//movement must also be blueprint callable to allow for input binding
	UFUNCTION(BluePrintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BluePrintCallable, Category = "Input")
		void IntendMoveBackward(float Throw);

	UFUNCTION(BluePrintCallable, Category = "Input")
	void IntendTurnRight(float Throw);

	UFUNCTION(BluePrintCallable, Category = "Input")
		void IntendTurnLeft(float Throw);


private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	

	
};
