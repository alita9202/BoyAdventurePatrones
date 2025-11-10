// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoOrco.h"
#include "AttackStrategy_Melee.h"

AEnemigoOrco::AEnemigoOrco()
{
    // Defaults del Orco
    VelocidadMovimiento = 320.f;   // un poco más rápido
    RadioDeteccion = 450.f;        // ligero extra de agro
}

void AEnemigoOrco::BeginPlay()
{
    Super::BeginPlay();
    if (!EstrategiaAtaque)
    {
        EstrategiaAtaque = NewObject<UAttackStrategy_Melee>(this);
    }
}