// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

		FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime) {

	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const{

	return Cast<ATank>(GetPawn());
}



void ATankPlayerController::AimTowardsCrosshair() {

	if (!ensure(GetControlledTank())){
		return;
	}

	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation)) { // is going to line trace
		//tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
}
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {


	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	//finds the location of the crosshair on the screen
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	//de-project the screen position of the crosshair to a world direction
	//line-trace along that look direction and see what we hit up to a maximum range
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {

	//const FName TraceTag("TraceTag");
	//GetWorld()->DebugDrawTraceTag = TraceTag;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetControlledPawn());
	//CollisionParams.TraceTag = TraceTag;
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		CollisionParams)
		) 
	
		{
		 HitLocation = HitResult.Location;
		 return true;
	}
	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation; // to be discarded
	return DeprojectScreenPositionToWorld
		(ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
		);
}


