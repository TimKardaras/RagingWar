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
}

ATank* ATankPlayerController::GetControlledTank() const{

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		return;
	}

}




