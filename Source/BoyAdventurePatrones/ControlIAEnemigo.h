// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ControlIAEnemigo.generated.h"

/**
 * 
 */
UCLASS()
class BOYADVENTUREPATRONES_API AControlIAEnemigo : public AAIController
{
	GENERATED_BODY()

public:
	AControlIAEnemigo();

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
