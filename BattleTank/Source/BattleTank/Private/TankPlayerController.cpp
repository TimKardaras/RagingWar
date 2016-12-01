// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();

	auto controlledTank = GetControlledTank();
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possessing a tank"));

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller possessing %s "), *(controlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const{

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		return;
	}

	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation)) { // is going to line trace
		//UE_LOG(LogTemp, Warning, TEXT("Hitlocation: %s"), *HitLocation.ToString());

		//tell controlled tank to aim at this point
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {


	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	//finds the location of the crosshair on the screen
	auto ScreenLocation = FVector2D(CrosshairXLocation * ViewportSizeX, CrosshairYLocation * ViewportSizeY);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation,LookDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());
	}
	//de-project the screen position of the crosshair to a world direction
	//line-trace along that look direction and see what we hit up to a maximum range
	return true;
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


