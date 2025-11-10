// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackStrategy.h"
#include "AttackStrategy_Ranged.generated.h"

/**
 * 
 */
class AProyectilEnemigo;

UCLASS()
class BOYADVENTUREPATRONES_API UAttackStrategy_Ranged : public UAttackStrategy
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Ranged")
    TSubclassOf<AProyectilEnemigo> ClaseProyectil;

    UPROPERTY(EditAnywhere, Category = "Ranged")
    float VelocidadProyectil = 1200.f;

    virtual void Execute(AEnemigoBase* Owner) override;
};
