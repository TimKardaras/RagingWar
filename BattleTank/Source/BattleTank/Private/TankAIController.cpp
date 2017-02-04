//TANK AI CONTROLLER.cpp
// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h" // so we can implement on death
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
	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire(); //TODO don't fire every frame
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) {
			return;
		}
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn()) {
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::AimAt(FVector HitLocation) {
}