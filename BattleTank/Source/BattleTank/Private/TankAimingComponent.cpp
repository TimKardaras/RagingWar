//TANK Aiming component.cpp

// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h" //cpp files need the h files but h files just need a forward declaration
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}



void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {

	Barrel = BarrelToSet;
	Turret = TurretToSet;

}
void UTankAimingComponent::Fire() {
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isReloaded) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		//FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	//UE_LOG(LogTemp, Warning, TEXT("Firing at %f"), LaunchSpeed);
	if (!ensure(Barrel)) {
		return;
	}
	if (!ensure(Turret)) {
		return;
	}

	//sets up the suggested projectile velocity
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this, //this object
		OutLaunchVelocity, //
		StartLocation, //startlocation
		HitLocation, //endlocation
		LaunchSpeed, //speed of projectile
		false,
		0,
		0
		, ESuggestProjVelocityTraceOption::DoNotTrace); //don't trace
	if (bHaveAimSolution)
	{
		//	UE_LOG(LogTemp, Warning, TEXT("HOUSTON WE HAVE A SOLUTION!"));
		//returns a new vector
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//sets the barrel according to the returned value from getsafenormal
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("Aim Solution found at %f"), Time);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	if (!ensure(Barrel && Turret)) { return; }
	//work out difference between current barrel rotation and aim direction
	//where the barrel is facing
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	//where the player is aiming
	auto AimAsRotator = AimDirection.Rotation();
	//the difference of rotation between the aim of the player and the location of the barrel
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//giving the Elevate function a value of 5
	Barrel->Elevate(DeltaRotator.Pitch); //this is where relative speed is set to 1

}

void UTankAimingComponent::MoveTurret(FVector AimDirection) {
	if (!ensure(Barrel && Turret)) { return; }
	//work out difference between current turret rotation and aim direction
	//where the turret is facing
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	//where the player is aiming
	auto AimAsRotator = AimDirection.Rotation();
	//the difference of rotation between the aim of the player and the location of the barrel
	auto DeltaRotator = AimAsRotator - TurretRotator;
	//giving the Elevate function a value of 5
	Turret->Azimuth(DeltaRotator.Yaw);
}

//void UTankAimingComponent::AimAt(FVector HitLocation) {
//	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
//}