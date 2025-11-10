// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "EnemyState.generated.h"

/**
 * 
 */
class AEnemigoBase;

UCLASS(Abstract, BlueprintType, Blueprintable)
class BOYADVENTUREPATRONES_API UEnemyState : public UObject
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "State")
    virtual void Enter(AEnemigoBase* Owner) {}

    UFUNCTION(BlueprintCallable, Category = "State")
    virtual void Tick(AEnemigoBase* Owner, float DeltaTime) {}

    UFUNCTION(BlueprintCallable, Category = "State")
    virtual void Exit(AEnemigoBase* Owner) {}
};
