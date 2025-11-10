// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemigoBase.generated.h"
class USphereComponent;
class AControlIAEnemigo;
class UEnemyState;        // Se implementará en PARTE 2
class UAttackStrategy;    // Se implementará en PARTE 2
class ARutaPatrulla;      // Se implementará en PARTE 2

UCLASS()
class BOYADVENTUREPATRONES_API AEnemigoBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemigoBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

    /** Detección del jugador (radio de agro) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Deteccion")
    USphereComponent* DeteccionJugador;

    /** Radio de detección (se aplicará al componente) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Deteccion")
    float RadioDeteccion;

    /** Velocidad de movimiento caminando */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movimiento")
    float VelocidadMovimiento;

    /** Referencia al jugador (si existe) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Objetivo")
    AActor* ObjetivoJugador;

    /** STATE (se implementará en PARTE 2) */
    UPROPERTY(VisibleAnywhere, Category = "Patrones|State")
    UEnemyState* EstadoActual;

    /** STRATEGY (se implementará en PARTE 2) */
    UPROPERTY(VisibleAnywhere, Category = "Patrones|Strategy")
    UAttackStrategy* EstrategiaAtaque;

    /** Ruta de patrulla (se agregará en PARTE 2) */
    UPROPERTY(EditAnywhere, Category = "Patrulla")
    ARutaPatrulla* RutaAsignada;

    /** Utilidad: distancia al jugador (si existe) */
    UFUNCTION(BlueprintCallable, Category = "Util")
    float DistanciaAlJugador() const;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Helpers de estado
    UFUNCTION()
    void CambiarEstado(class UEnemyState* Nuevo);

    UFUNCTION()
    void CambiarAEstadoPatrulla();

    UFUNCTION()
    void CambiarAEstadoAtaque();

    // Helper Strategy
    UFUNCTION()
    void EjecutarAtaque();

    // Llegada a destino (chequeo básico usando distancia horizontal)
    bool HaLlegadoAlDestino(float ToleranciaPlano) const;

    UPROPERTY(VisibleAnywhere, Category = "Visual")
    UStaticMeshComponent* Visual;

private:
    // Guardar último destino para chequeo simple en Patrulla (opcional)
    FVector UltimoDestino;
};
