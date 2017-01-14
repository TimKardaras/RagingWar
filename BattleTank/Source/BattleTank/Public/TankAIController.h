// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
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

	//how close an AI tank can get to the player
	float AcceptanceRadius = 3000;
	
};
