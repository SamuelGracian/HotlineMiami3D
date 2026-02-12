// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapons.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	/// --MESH-- ///
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}

	// sensible defaults
	CurrentAmmoInMagazine = MagazineSize;
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


bool ABaseWeapon::CanFire() const
{
	if (bIsReloading)
	{
		return false;
	}

	if (FiringMode == EWeaponFiringMode::Melee)
	{
		return true;
	}

	if (bInfiniteAmmo)
	{
		return true;
	}

	return CurrentAmmoInMagazine > 0;
}

void ABaseWeapon::StartFire()
{
	bWantsToFire = true;

	if (!CanFire())
	{
		return;
	}

	switch (FiringMode)
	{
	case EWeaponFiringMode::Automatic:
	{
		GetWorldTimerManager().SetTimer(TimerHandle_AutoFire, this, &ABaseWeapon::HandleFire, 2.0f, true, 0.0f);
		// Fire immediately
		HandleFire();
		break;
	}
	case EWeaponFiringMode::SemiAuto:
	{

		FireOnce();
		break;
	}
	case EWeaponFiringMode::Melee:
	{
		FireOnce();
		break;
	}
	default:
		break;
	}
}

void ABaseWeapon::StopFire()
{
	bWantsToFire = false;

	if (TimerHandle_AutoFire.IsValid())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_AutoFire);
	}

}

void ABaseWeapon::FireOnce()
{
	if (!CanFire()) return;

	HandleFire();
}

void ABaseWeapon::HandleFire()
{


	PerformHit();

	ConsumeAmmo();

	OnWeaponFired();

	if (FiringMode == EWeaponFiringMode::SemiAuto || FiringMode == EWeaponFiringMode::Melee)
	{
		return;
	}
}

void ABaseWeapon::PerformHit()
{
	FVector Start = GetMuzzleLocation();
	FRotator Rot = GetMuzzleRotation();
	FVector ShotDirection = Rot.Vector();

	float HalfRad = FMath::DegreesToRadians(SpreadDegrees * 0.5f);
	ShotDirection = FMath::VRandCone(ShotDirection, HalfRad);

	FVector End = Start + ShotDirection * Range;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	if (GetOwner())
	{
		Params.AddIgnoredActor(GetOwner());
	}

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
#if WITH_EDITOR

	DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 1.0f, 0, 1.0f);
#endif
	if (bHit)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			UGameplayStatics::ApplyPointDamage(HitActor, Damage, ShotDirection, Hit, GetInstigatorController(), this, nullptr);
		}
	}
}

void ABaseWeapon::ConsumeAmmo()
{
	if (FiringMode == EWeaponFiringMode::Melee)
	{
		return;
	}

	if (bInfiniteAmmo)
	{
		return;
	}
									  
	if (CurrentAmmoInMagazine > 0)
	{
		--CurrentAmmoInMagazine;
	}
	else
	{								 
	}
}

FVector ABaseWeapon::GetMuzzleLocation() const
{
	return GetActorLocation();
}
						  

FRotator ABaseWeapon::GetMuzzleRotation() const
{
	return GetActorRotation();
}