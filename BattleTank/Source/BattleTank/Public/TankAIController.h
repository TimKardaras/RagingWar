//TANK AI CONTROLLER.h

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "TankAIController.generated.h"

/**
*
*/
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);
private:
	void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	//how close an AI tank can get to the player
	UPROPERTY(EditAnywhere, Category = "Setup")
		float AcceptanceRadius = 80000;

};
