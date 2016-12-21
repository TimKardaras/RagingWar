// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

//New tank Barrel static mesh created for tank to allow code 
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 max downward speed, +1 is max upward speed
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = BarrelElevation)
	float MaxDegreesPerSecond = 10; //set to 5 after testing

	UPROPERTY(EditAnywhere, Category = BarrelElevation)
	float MaxElevationDegrees = 40; // the maximum elevation of the barrel is 40 degrees above the current angle

	UPROPERTY(EditAnywhere, Category = BarrelElevation)
	float MinElevationDegrees = 0; // so the minimum elevation of the barrel is going to be where it currently is
	
	
	
};
