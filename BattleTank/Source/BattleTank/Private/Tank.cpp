//TANK.CPP
// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTrack.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Tank.h"

ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}
float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) {
	
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	auto DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Damage is: %f damage to apply is %i"),DamageAmount, DamageToApply);
	UE_LOG(LogTemp, Warning, TEXT("You now have %i health"), CurrentHealth);
	if (CurrentHealth == 0) {
		OnDeath.Broadcast();
	}
	return DamageToApply;
}

float ATank::GetCurrentHealth() const
{
	return (float)CurrentHealth /(float)StartingHealth;
}


