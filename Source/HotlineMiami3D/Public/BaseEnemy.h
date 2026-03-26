// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseWeapons.h"
#include "BaseEnemy.generated.h"

class ABaseWeapon;

UCLASS()
class HOTLINEMIAMI3D_API ABaseEnemy : public APawn 
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "Equiped Weapon")
    ABaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY(EditAnywhere, Category = "Enemy stats")
	int CurrentHealth;

	UPROPERTY(EditAnywhere, Category = "Enemy stats")
	int MaxHealth;

};
