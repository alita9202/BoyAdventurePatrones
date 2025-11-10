// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackStrategy.h"
#include "AttackStrategy_Melee.generated.h"

/**
 * 
 */
UCLASS()
class BOYADVENTUREPATRONES_API UAttackStrategy_Melee : public UAttackStrategy
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Melee")
    float RangoMelee = 160.f;

    UPROPERTY(EditAnywhere, Category = "Melee")
    float Danio = 10.f;

    virtual void Execute(AEnemigoBase* Owner) override;
};
