// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BoyAdventurePatronesGameMode.generated.h"

class AFacadePlataforma;

UCLASS(minimalapi)
class ABoyAdventurePatronesGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABoyAdventurePatronesGameMode();

protected:
	virtual void BeginPlay() override;


	/** Cantidad de armas al iniciar */
	UPROPERTY(EditAnywhere, Category = "Armas|Spawn")
	int32 NumArmas = 8;

	/** Radio de búsqueda alrededor del PlayerStart (o 0,0,0) */
	UPROPERTY(EditAnywhere, Category = "Armas|Spawn")
	float RadioSpawn = 4000.f;

	/** Distancia mínima entre armas spawneadas */
	UPROPERTY(EditAnywhere, Category = "Armas|Spawn")
	float DistanciaMinima = 200.f;

	/** Intentos máximos por arma para hallar punto válido */
	UPROPERTY(EditAnywhere, Category = "Armas|Spawn")
	int32 MaxIntentosPorArma = 25;

private:
	FVector ObtenerCentroSpawn() const;
	bool EsValido(const FVector& Punto, const TArray<FVector>& Usados) const;
	bool EncontrarPuntoAleatorioValido(const FVector& Centro, FVector& OutPunto, const TArray<FVector>& Usados) const;
	void SpawnArmasAleatorias();

public:
	// Referencia a la fachada de plataformas
	UPROPERTY(VisibleAnywhere, Category = "Referencias")
	AFacadePlataforma* FacadePlataforma;

	// Clase que se usará para crear la fachada
	UPROPERTY(EditAnywhere, Category = "Configuración")
	TSubclassOf<AFacadePlataforma> ClaseFacadePlataforma;

	// Ejemplo: activa la animación de un piso específico
	UFUNCTION(BlueprintCallable, Category = "Acciones")
	void ActivarAnimacionPiso(int32 Piso);

	// Ejemplo: aplica efecto al jugador en todas las plataformas
	UFUNCTION(BlueprintCallable, Category = "Acciones")
	void AfectarJugadorEnPlataformas(AActor* Jugador);

};



