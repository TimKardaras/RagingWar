// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {

	//TODO Clamp actual throttle value

	//applying the force, what does get forward vector do?
	// throttle * the max driving force
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	//gets the location of the component
	auto ForceLocation = GetComponentLocation();
	// gets the component that needs to have a force acted onto it
	auto TankRoot = Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


