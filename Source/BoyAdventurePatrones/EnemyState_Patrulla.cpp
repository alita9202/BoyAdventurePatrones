// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyState_Patrulla.h"
#include "EnemigoBase.h"
#include "RutaPatrulla.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"


UEnemyState_Patrulla::UEnemyState_Patrulla()
{
    PuntoActual = 0;
}

void UEnemyState_Patrulla::Enter(AEnemigoBase* Owner)
{
    PuntoActual = 0;
    SolicitarMovimientoAlPunto(Owner);
}

void UEnemyState_Patrulla::Tick(AEnemigoBase* Owner, float DeltaTime)
{
    if (!Owner) return;

    const float Dist = Owner->DistanciaAlJugador();
    if (Dist <= Owner->RadioDeteccion * 0.95f)
    {
        UE_LOG(LogTemp, Warning, TEXT("[State_Patrulla] Jugador detectado (Dist=%.1f). Cambiar a ATAQUE"), Dist);
        Owner->CambiarAEstadoAtaque();
        return;
    }

    if (Owner->HaLlegadoAlDestino(100.f))
    {
        AvanzarPunto(Owner);
        SolicitarMovimientoAlPunto(Owner);
    }
}

void UEnemyState_Patrulla::AvanzarPunto(AEnemigoBase* Owner)
{
    if (!Owner || !Owner->RutaAsignada) return;
    const int32 Num = Owner->RutaAsignada->NumPuntos();
    if (Num <= 0) return;

    PuntoActual = (PuntoActual + 1) % Num;
}

void UEnemyState_Patrulla::SolicitarMovimientoAlPunto(AEnemigoBase* Owner)
{
    if (!Owner || !Owner->RutaAsignada) return;
    AActor* Punto = Owner->RutaAsignada->GetPunto(PuntoActual);
    if (!Punto) return;

    if (AAIController* AI = Cast<AAIController>(Owner->GetController()))
    {
        AI->MoveToActor(Punto, 5.f, true, true, true, 0, true);
    }
}