// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArmaSpawnManager.generated.h"

UCLASS()
class BOYADVENTUREPATRONES_API AArmaSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArmaSpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Área de spawneo
	UPROPERTY(VisibleAnywhere, Category = "Spawn")
	class UBoxComponent* SpawnArea;

	// Cuántas armas generar
	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 NumArmas = 5;

	// Separación mínima entre spawns (para evitar superposición visual básica)
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float DistanciaMinima = 150.f;

	// Intentos máximos para hallar un punto válido por arma
	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 MaxIntentosPorArma = 20;

	// Utilidad: genera un punto aleatorio dentro del box
	FVector GetRandomPointInBox() const;

	// Comprueba distancia mínima con ya colocados
	bool EsValido(const FVector& Punto, const TArray<FVector>& Usados) const;

};
