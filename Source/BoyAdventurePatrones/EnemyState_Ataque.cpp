// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyState_Ataque.h"
#include "EnemigoBase.h"
#include "AIController.h"

void UEnemyState_Ataque::Enter(AEnemigoBase* Owner)
{
    TiempoAcumulado = 0.f;
    CadenciaAtaque = 1.0f;
    UE_LOG(LogTemp, Warning, TEXT("[State_Ataque] Enter"));
}

void UEnemyState_Ataque::Tick(AEnemigoBase* Owner, float DeltaTime)
{
    if (!Owner) return;

    const float Dist = Owner->DistanciaAlJugador();

    // Si sale del rango (un pequeño margen), volver a patrulla y detener movimiento
    if (Dist > Owner->RadioDeteccion * 1.05f)
    {
        UE_LOG(LogTemp, Warning, TEXT("[State_Ataque] Fuera de rango (Dist=%.1f). Volver a PATRULLA"), Dist);
        if (AAIController* AI = Cast<AAIController>(Owner->GetController()))
        {
            AI->StopMovement();
            AI->ClearFocus(EAIFocusPriority::Gameplay);
        }
        Owner->CambiarAEstadoPatrulla();
        return;
    }

    // Perseguir al jugador
    if (AAIController* AI = Cast<AAIController>(Owner->GetController()))
    {
        if (Owner->ObjetivoJugador)
        {
            AI->SetFocus(Owner->ObjetivoJugador);
            AI->MoveToActor(Owner->ObjetivoJugador, 150.f, true, true, true, 0, true);
        }
    }

    // Cadencia de ataque
    TiempoAcumulado += DeltaTime;
    if (TiempoAcumulado >= CadenciaAtaque)
    {
        TiempoAcumulado = 0.f;
        Owner->EjecutarAtaque();
    }
}
