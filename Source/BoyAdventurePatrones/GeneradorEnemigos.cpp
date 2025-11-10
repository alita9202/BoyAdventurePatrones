// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneradorEnemigos.h"
#include "RutaPatrulla.h"
#include "EnemigoBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"

// Sets default values
AGeneradorEnemigos::AGeneradorEnemigos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGeneradorEnemigos::BeginPlay()
{
	Super::BeginPlay();

    // Crear o asegurar ruta si se configuró así
    AsegurarRuta();

    // Spawn múltiple
    for (int32 i = 0; i < CantidadInicial; ++i)
    {
        SpawnUno(ElegirTipo());
    }

}
ETipoEnemigo AGeneradorEnemigos::ElegirTipo() const
{
    if (bAleatorio)
    {
        return (FMath::RandBool()) ? ETipoEnemigo::Orco : ETipoEnemigo::Fantasma;
    }
    return TipoPorDefecto;
}

void AGeneradorEnemigos::SpawnUno(ETipoEnemigo Tipo)
{
    TSubclassOf<AEnemigoBase> Clase = nullptr;

    switch (Tipo)
    {
    case ETipoEnemigo::Orco:
        Clase = ClaseOrco;
        break;
    case ETipoEnemigo::Fantasma:
        Clase = ClaseFantasma;
        break;
    }

    if (!Clase) return;

    const FVector Centro = GetActorLocation();
    const FVector Offset = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, RadioSpawn);
    const FVector PosSpawn = Centro + Offset;
    const FRotator Rot = GetActorRotation();

    FActorSpawnParameters Params;
    Params.Owner = this;

    AEnemigoBase* Enemigo = GetWorld()->SpawnActor<AEnemigoBase>(Clase, PosSpawn, Rot, Params);
    if (Enemigo)
    {
        if (RutaParaAsignar)
        {
            Enemigo->RutaAsignada = RutaParaAsignar;
        }

        // Log visual para confirmar
        if (GEngine)
        {
            const FString TipoTxt = (Tipo == ETipoEnemigo::Orco) ? TEXT("Orco") : TEXT("Fantasma");
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green,
                FString::Printf(TEXT("Spawn: %s en %s"), *TipoTxt, *PosSpawn.ToString()));
        }
    }
}

/** ------------------------------------------------------------------ */
/** Ruta automática                                                     */
/** ------------------------------------------------------------------ */

void AGeneradorEnemigos::AsegurarRuta()
{
    if (RutaParaAsignar)
    {
        return; // Ya hay una ruta manual
    }

    if (!bCrearRutaAuto)
    {
        return; // No se desea crear ruta automática
    }

    RutaParaAsignar = CrearRutaCuadrada();
    if (!RutaParaAsignar)
    {
        UE_LOG(LogTemp, Warning, TEXT("GeneradorEnemigos: No fue posible crear la ruta automática."));
        return;
    }

    PoblarRutaConPuntos(RutaParaAsignar);
}

ARutaPatrulla* AGeneradorEnemigos::CrearRutaCuadrada()
{
    FActorSpawnParameters Params;
    Params.Owner = this;

    const FVector Pos = GetActorLocation();
    const FRotator Rot = FRotator::ZeroRotator;

    ARutaPatrulla* Ruta = GetWorld()->SpawnActor<ARutaPatrulla>(ARutaPatrulla::StaticClass(), Pos, Rot, Params);
    return Ruta;
}

void AGeneradorEnemigos::PoblarRutaConPuntos(ARutaPatrulla* Ruta)
{
    if (!Ruta) return;

    Ruta->Puntos.Empty();

    // Si NumPuntosRuta==4, dibujamos un cuadrado; si es >4, hacemos un círculo de puntos
    if (NumPuntosRuta == 4)
    {
        const float R = RadioRuta;
        const FVector C = GetActorLocation();

        TArray<FVector> Posiciones;
        Posiciones.Add(C + FVector(+R, +R, 0.f));
        Posiciones.Add(C + FVector(+R, -R, 0.f));
        Posiciones.Add(C + FVector(-R, -R, 0.f));
        Posiciones.Add(C + FVector(-R, +R, 0.f));

        for (const FVector& P : Posiciones)
        {
            ATargetPoint* TP = GetWorld()->SpawnActor<ATargetPoint>(ATargetPoint::StaticClass(), P, FRotator::ZeroRotator);
            if (TP) Ruta->Puntos.Add(TP);
        }
    }
    else
    {
        // Distribución circular
        const FVector C = GetActorLocation();
        const float R = RadioRuta;
        for (int32 i = 0; i < NumPuntosRuta; ++i)
        {
            const float Ang = (2.f * PI * i) / static_cast<float>(NumPuntosRuta);
            const FVector P = C + FVector(FMath::Cos(Ang) * R, FMath::Sin(Ang) * R, 0.f);
            ATargetPoint* TP = GetWorld()->SpawnActor<ATargetPoint>(ATargetPoint::StaticClass(), P, FRotator::ZeroRotator);
            if (TP) Ruta->Puntos.Add(TP);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("GeneradorEnemigos: Ruta auto creada con %d puntos."), Ruta->Puntos.Num());
}


