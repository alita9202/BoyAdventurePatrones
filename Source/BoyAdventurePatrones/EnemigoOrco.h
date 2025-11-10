// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemigoBase.h"
#include "EnemigoOrco.generated.h"

/**
 * 
 */
UCLASS()
class BOYADVENTUREPATRONES_API AEnemigoOrco : public AEnemigoBase
{
	GENERATED_BODY()

public:
	AEnemigoOrco();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
