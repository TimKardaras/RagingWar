// copyright Tim Kardaras

#pragma once

//#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
class ATank;
class UTankAimingComponent;
/**
 * responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	//start the tank moving the barrel so that a shot would hit
	//where the crosshair intersects the world
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.2f;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;

};
