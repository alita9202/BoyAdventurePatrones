// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyState.h"
#include "EnemyState_Patrulla.generated.h"

/**
 * 
 */
UCLASS()
class BOYADVENTUREPATRONES_API UEnemyState_Patrulla : public UEnemyState
{
	GENERATED_BODY()

public:
    UEnemyState_Patrulla();

    virtual void Enter(AEnemigoBase* Owner) override;
    virtual void Tick(AEnemigoBase* Owner, float DeltaTime) override;

private:
    int32 PuntoActual;
    void AvanzarPunto(AEnemigoBase* Owner);
    void SolicitarMovimientoAlPunto(AEnemigoBase* Owner);
};
