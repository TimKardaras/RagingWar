//TANK.H

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // no includes below this line

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
		// Sets default values for this pawn's properties
public:
	
	//returns current health
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetCurrentHealth() const;
	//called by the engine when Actor damage is dealt
virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
// Called when the game starts or when spawned

FTankDelegate OnDeath;
private:
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth;

	virtual void BeginPlay() override;
};