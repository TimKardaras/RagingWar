// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h" //cpp files need the h files but h files just need a forward declaration
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	//Barrel is initialized to barreltoset to set the barrels location?
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	//UE_LOG(LogTemp, Warning, TEXT("Firing at %f"), LaunchSpeed);
	if (!Barrel) {
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
		ESuggestProjVelocityTraceOption::DoNotTrace); //don't trace
		if(bHaveAimSolution)
	{
		//returns a new vector
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//sets the barrel according to the returned value from getsafenormal
			MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	//work out difference between current barrel rotation and aim direction
	//where the barrel is facing
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	//where the player is aiming
	auto AimAsRotator = AimDirection.Rotation();
	//the difference of rotation between the aim of the player and the location of the barrel
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//giving the Elevate function a value of 5
	Barrel->Elevate(5);

}
