// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "AttackStrategy.generated.h"

/**
 * 
 */
class AEnemigoBase;

UCLASS(Abstract, BlueprintType, Blueprintable)
class BOYADVENTUREPATRONES_API UAttackStrategy : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Strategy")
	virtual void Execute(AEnemigoBase* Owner) {}
};
