// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemigoBase.h"
#include "EnemigoFantasma.generated.h"

/**
 * 
 */
UCLASS()
class BOYADVENTUREPATRONES_API AEnemigoFantasma : public AEnemigoBase
{
	GENERATED_BODY()

public:
	AEnemigoFantasma();

protected:
	virtual void BeginPlay() override;
};
