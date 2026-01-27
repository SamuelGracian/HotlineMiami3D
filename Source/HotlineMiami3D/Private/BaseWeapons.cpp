// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapons.h"

// Sets default values
ABaseWeapons::ABaseWeapons()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// --MESH-- ///
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}

}

// Called when the game starts or when spawned
void ABaseWeapons::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

