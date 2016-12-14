// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	//player tank is equal to the first player controller's tank
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller cannot find player tank"));

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controller found player tank: %s "), *(PlayerTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {

		//the controlled tank will aim at the location of the player's tank
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		//TODO Move towards the player

		//Aim towards the player

		//fire if ready
	}
}

void ATankAIController::AimAt(FVector HitLocation) {
}

ATank* ATankAIController::GetControlledTank() const {
	//returns the players tank
	return Cast<ATank>(GetPawn());
}



ATank* ATankAIController::GetPlayerTank() const {

	//finds the first player within the world
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	else {
		//returns the players tank
		return Cast<ATank>(PlayerPawn);
	}

}
