// Copyright Tim Kardaras.

#pragma once

#include "GameFramework/Actor.h"
#include "Gun.generated.h"

//class AGunProjectile;
UCLASS()
class BATTLETANK_API AGun : public AActor
{
	GENERATED_BODY()
	
		/** Gun mesh: 1st person view (seen only by self) */
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;
public:	
	// Sets default values for this actor's properties
	AGun();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;



	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AGunProjectile> ProjectileClass;

	/*UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AGunProjectile> ProjectileCdlass;*/

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimInstance* AnimInstance;

	/** Fires a projectile. */
	UFUNCTION(BluePrintCallable, Category = "Firing")
		void OnFire();



	
	
};
