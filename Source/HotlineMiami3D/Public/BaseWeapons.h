// Fill out your copyright notice in the Description page of Project Settings.

#pragma once	
#include "CoreMinimal.h"

#include "BaseWeapons.generated.h"

	UENUM(BlueprintType)
	enum class EWeaponFiringMode : uint8
	{
		Automatic	UMETA(DisplayName = "Automatic"),
		SemiAuto	UMETA(DisplayName = "Semi-Automatic"),
		Melee		UMETA(DisplayName = "Melee")
	};


	UENUM (BlueprintType)
	enum class PickedUpState : uint8
	{
		Enemy  UMETA(DisplayName = "Picked up by enemy"),
		Floor  UMETA(DisplayName = "Weapon on floor"),
		Player UMETA(DisplayName = "Picked up by player")
	};

	UCLASS(Blueprintable)
	class HOTLINEMIAMI3D_API ABaseWeapon : public AActor

	{
	public:
		GENERATED_BODY()
		ABaseWeapon();

protected:
	// --- Components / internal fields required by .cpp ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Stas")
	UStaticMeshComponent* MeshComponent = nullptr;

	// --- Configurable properties ---
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	EWeaponFiringMode FiringMode = EWeaponFiringMode::SemiAuto;

	// Weapon stats
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	int32 MagazineSize = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Stats")
	int32 CurrentAmmoInMagazine = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	bool bInfiniteAmmo = false;

	// Rounds per minute
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats|Ranged", meta = (ClampMin = "1.0"))
	float RateOfFireRPM = 600.0f;

	// Damage, range and spread
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats|Ranged")
	float Damage = 25.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats|Ranged")
	float Range = 10000.0f;

	// Spread in degrees used by PerformHit()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats|Ranged")
	float SpreadDegrees = 1.0f;

	// Melee stats
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats|Melee")
	float MeleeRange = 150.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats|Melee")
	float MeleeDamage = 40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon State")
    PickedUpState CurrentPickedUpState = PickedUpState::Floor;

	// --- Internal state ---
	FTimerHandle TimerHandle_AutoFire;

	bool bWantsToFire = false;

	bool bIsReloading = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:


	// API
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StopFire();

	// Fire a single shot immediately (useful for semi-auto or forced single shot)
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void FireOnce();

	// Helpers
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool CanFire() const;

	// Blueprint events
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Weapon|Events")
	void OnWeaponFired();


    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Weapon|Events")
    void OnWeaponEquiped(ACharacter* newOwner);

protected:

	virtual void HandleFire();

	virtual void PerformHit();

	virtual void ConsumeAmmo();

												
	//utilities
		// Utility
	virtual FVector GetMuzzleLocation() const;
	virtual FRotator GetMuzzleRotation() const;

};
