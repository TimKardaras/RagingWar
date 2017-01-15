// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // no includes below this line

class UTankBarrel;
class UTankTurret;
class UTankTrack;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	UTankAimingComponent* TankAimingComponent = nullptr;

	//making it a uproperty allows us to use it in blueprint
	UPROPERTY(BlueprintReadOnly, Category = "State")
	UTankMovementComponent* TankMovementComponent = nullptr;
public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BluePrintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BluePrintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BluePrintCallable, Category = Firing)
		void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000; //TODO find sensible value
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.0f;

	//local barrel reference for spawning proectile
	UTankBarrel* Barrel = nullptr;

	double LastFireTime = -3;
	
	
};
