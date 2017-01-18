//TANK AI CONTROLLER.cpp
// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	//finds the first player within the world
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	//move to actor
	MoveToActor(PlayerTank, AcceptanceRadius);
	//the controlled tank will aim at the location of the player's tank
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	//TODO Move towards the player
	AimingComponent->Fire(); //TODO don't fire every frame
}

void ATankAIController::AimAt(FVector HitLocation) {
}