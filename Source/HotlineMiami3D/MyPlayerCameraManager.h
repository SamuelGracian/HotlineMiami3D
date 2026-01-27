// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "MyPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HOTLINEMIAMI3D_API AMyPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
	public:

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void UpdateCamera();

};
