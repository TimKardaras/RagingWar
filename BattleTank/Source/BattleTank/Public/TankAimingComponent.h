// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum here
UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Loading,
	Reloaded
};

//cpp files need the include h files but h files just need a forward declaration like so 
class UTankBarrel;
class UTankTurret;

//Holds Barrels Properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties


	void AimAt(FVector HitLocation, float LaunchSpeed);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Loading;
private:
	UTankAimingComponent();

	//initialize the barrel to null
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;
	
	void MoveBarrel(FVector AimDirection);

	void MoveTurret(FVector AimDirection);
};
