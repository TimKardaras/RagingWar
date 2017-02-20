// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"


UTankTrack::UTankTrack() {

	PrimaryComponentTick.bCanEverTick = true;

}

void UTankTrack::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	// Store our initial location  
}



void UTankTrack::ApplySidewaysForce() {
	// Solves the slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//corrects the acceleration to avoid slippage

	//DeltaTime = Time in Game

	//Worked out the correct acceleration
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//gets the root component to get the tank mass
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	//F=ma
	//calculated and applied the sideways friction
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}



void UTankTrack::DriveTrack(){

	//TODO Clamp actual throttle value

	//applying the force, what does get forward vector do?
	// throttle * the max driving force
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	//gets the location of the component
	auto ForceLocation = GetComponentLocation();
	// gets the component that needs to have a force acted onto it
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::SetThrottle(float Throttle) {
	//CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 5);
	CurrentThrottle += Throttle;
}


