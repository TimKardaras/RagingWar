// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
//UCLASS()
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//does nothing at the moment
	void Elevate(float DegreesPerSecond);

private:
	UPROPERTY(EditAnywhere, Category = BarrelElevation)
	float MaxDegreesPerSecond = 20; //sensible default

	UPROPERTY(EditAnywhere, Category = BarrelElevation)
	float MaxElevationDegrees = 40; // the maximum elevation of the barrel is 40 degrees above the current angle

	UPROPERTY(EditAnywhere, Category = BarrelElevation)
	float MinElevationDegrees = 0; // so the minimum elevation of the barrel is going to be where it currently is
	
	
	
};
