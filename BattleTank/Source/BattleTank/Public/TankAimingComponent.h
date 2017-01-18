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
class AProjectile;

//Holds Barrels Properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties

	UFUNCTION(BluePrintCallable, Category = "Firing")
	void Fire();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Loading;
private:
	UTankAimingComponent();


	void MoveBarrel(FVector AimDirection);

	void MoveTurret(FVector AimDirection);

	double LastFireTime = -3;
	//initialize the barrel to null
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;
	

	// Called to bind functionality to input
	/*virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;*/

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3.0f;

};
