// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Azimuth(float RelativeSpeed) {
	//speed is clamped but rotation is not
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto Rotation = RelativeRotation.Yaw + AzimuthChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));

}



