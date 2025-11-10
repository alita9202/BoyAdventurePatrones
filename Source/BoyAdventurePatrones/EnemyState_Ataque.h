// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyState.h"
#include "EnemyState_Ataque.generated.h"

/**
 * 
 */
UCLASS()
class BOYADVENTUREPATRONES_API UEnemyState_Ataque : public UEnemyState
{
	GENERATED_BODY()

public:
    virtual void Enter(AEnemigoBase* Owner) override;
    virtual void Tick(AEnemigoBase* Owner, float DeltaTime) override;

private:
    float TiempoAcumulado;
    float CadenciaAtaque; // segundos entre ejecuciones
};
