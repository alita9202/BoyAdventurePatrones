// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// --- ENUM agregado aquí ---
UENUM(BlueprintType)
enum class ETipoEnemigo : uint8
{
    Orco     UMETA(DisplayName = "Orco"),
    Fantasma UMETA(DisplayName = "Fantasma")
};

#include "GeneradorEnemigos.generated.h"

class ARutaPatrulla;
class AEnemigoBase;

UCLASS()
class BOYADVENTUREPATRONES_API AGeneradorEnemigos : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneradorEnemigos();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
    /** Clases concretas a instanciar */
    UPROPERTY(EditAnywhere, Category = "Generador|Clases")
    TSubclassOf<AEnemigoBase> ClaseOrco;

    UPROPERTY(EditAnywhere, Category = "Generador|Clases")
    TSubclassOf<AEnemigoBase> ClaseFantasma;

    /** Tipo por defecto (si Aleatorio=false) */
    UPROPERTY(EditAnywhere, Category = "Generador|Spawn")
    ETipoEnemigo TipoPorDefecto = ETipoEnemigo::Orco;

    /** ¿Spawnear tipos aleatorios? */
    UPROPERTY(EditAnywhere, Category = "Generador|Spawn")
    bool bAleatorio = true;

    /** Cuántos enemigos crear en BeginPlay */
    UPROPERTY(EditAnywhere, Category = "Generador|Spawn", meta = (ClampMin = "0"))
    int32 CantidadInicial = 4;

    /** Radio aleatorio de aparición alrededor del Generador */
    UPROPERTY(EditAnywhere, Category = "Generador|Spawn", meta = (ClampMin = "0"))
    float RadioSpawn = 200.f;

    /** Ruta para asignar a cada enemigo (opcional). Si está vacío y bCrearRutaAuto=true, se creará una. */
    UPROPERTY(EditAnywhere, Category = "Generador|Patrulla")
    ARutaPatrulla* RutaParaAsignar;

    /** Crear automáticamente una ruta si no hay una asignada */
    UPROPERTY(EditAnywhere, Category = "Generador|Patrulla")
    bool bCrearRutaAuto = true;

    /** Parámetros de la ruta automática */
    UPROPERTY(EditAnywhere, Category = "Generador|Patrulla", meta = (EditCondition = "bCrearRutaAuto", ClampMin = "3"))
    int32 NumPuntosRuta = 4;

    UPROPERTY(EditAnywhere, Category = "Generador|Patrulla", meta = (EditCondition = "bCrearRutaAuto", ClampMin = "100"))
    float RadioRuta = 600.f;

private:
    void SpawnUno(ETipoEnemigo Tipo);
    ETipoEnemigo ElegirTipo() const;

    void AsegurarRuta();
    ARutaPatrulla* CrearRutaCuadrada();
    void PoblarRutaConPuntos(ARutaPatrulla* Ruta);
};
