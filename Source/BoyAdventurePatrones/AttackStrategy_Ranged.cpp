// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackStrategy_Ranged.h"
#include "EnemigoBase.h"
#include "ProyectilEnemigo.h"
#include "Kismet/GameplayStatics.h"

void UAttackStrategy_Ranged::Execute(AEnemigoBase* Owner)
{
    if (!Owner || !Owner->ObjetivoJugador || !ClaseProyectil) return;

    UWorld* World = Owner->GetWorld();
    if (!World) return;

    const FVector Origen = Owner->GetActorLocation() + FVector(0, 0, 50);
    const FVector Objetivo = Owner->ObjetivoJugador->GetActorLocation();
    const FVector Dir = (Objetivo - Origen).GetSafeNormal();

    FActorSpawnParameters Params;
    Params.Owner = Owner;
    Params.Instigator = Owner;

    AProyectilEnemigo* Proy = World->SpawnActor<AProyectilEnemigo>(ClaseProyectil, Origen, Dir.Rotation(), Params);
    if (Proy)
    {
        Proy->DispararEnDireccion(Dir, VelocidadProyectil);
    }
}
