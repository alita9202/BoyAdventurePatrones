// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackStrategy_Melee.h"
#include "EnemigoBase.h"
#include "Kismet/GameplayStatics.h"

void UAttackStrategy_Melee::Execute(AEnemigoBase* Owner)
{
    if (!Owner || !Owner->ObjetivoJugador) return;

    const float Dist = FVector::Dist(Owner->GetActorLocation(), Owner->ObjetivoJugador->GetActorLocation());
    if (Dist <= RangoMelee)
    {
        // Aquí podrías aplicar daño real si tu jugador implementa un sistema de salud
        // Por ahora dejamos un efecto/feedback sencillo:
        UGameplayStatics::PlaySoundAtLocation(Owner, nullptr, Owner->GetActorLocation()); // placeholder sin sonido
        // También podrías imprimir log:
        UE_LOG(LogTemp, Log, TEXT("Melee hit al jugador (simulado)."));
    }
}
