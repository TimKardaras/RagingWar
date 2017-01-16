// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed) {
	//clamping the speed of the barrel between -1 and +1
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	//setting the elevation change to the speed * the max amount of degrees per second * the current frame
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	// sets the elevation to the elevation change
	auto UnclampedNewElevation = RelativeRotation.Pitch + ElevationChange;
	//clamps the elevation of the barrel between 0 degrees and 40 degrees
	auto Elevation = FMath::Clamp<float>(UnclampedNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Barrel elevate called at speed %f"), RelativeSpeed);
}

