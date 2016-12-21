// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Azimuth(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = BarrelAzimuth)
		float MaxDegreesPerSecond = 25; //set to 5 after testing
};
