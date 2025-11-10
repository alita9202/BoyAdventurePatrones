// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoFantasma.h"
#include "AttackStrategy_Ranged.h"
#include "ProyectilEnemigo.h"

AEnemigoFantasma::AEnemigoFantasma()
{
    // Defaults del Fantasma
    VelocidadMovimiento = 280.f; // más lento
    RadioDeteccion = 450.f;      // detecta desde más lejos (ideal para ataque a distancia)
}

void AEnemigoFantasma::BeginPlay()
{
    Super::BeginPlay();

    if (!EstrategiaAtaque)
    {
        UAttackStrategy_Ranged* Estr = NewObject<UAttackStrategy_Ranged>(this);
        // Asignar clase de proyectil por defecto (puedes cambiar a un BP si prefieres)
        Estr->ClaseProyectil = AProyectilEnemigo::StaticClass();
        EstrategiaAtaque = Estr;
    }
}