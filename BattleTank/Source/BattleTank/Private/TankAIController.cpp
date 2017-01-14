// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	//finds the first player within the world
	if (PlayerTank) {
		//move to actor
		MoveToActor(PlayerTank, AcceptanceRadius);
		//the controlled tank will aim at the location of the player's tank
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//TODO Move towards the player
		ControlledTank->Fire(); //TODO don't fire every frame
	}
}

void ATankAIController::AimAt(FVector HitLocation) {
}

