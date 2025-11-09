// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArmaBaseBuilder.h"
#include "ArmaDirector.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BOYADVENTUREPATRONES_API UArmaDirector : public UObject
{
	GENERATED_BODY()

public:
	// Construye y devuelve el arma ya configurada
	UFUNCTION(BlueprintCallable, Category = "Builder")
	AArmaBase* Construir(UWorld* World, UArmaBaseBuilder* Builder, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator)
	{
		if (!World || !Builder) return nullptr;

		Builder->CrearNuevaArma(World, Location, Rotation);
		AArmaBase* Resultado = Builder->ObtenerResultado();
		if (!Resultado) return nullptr;

		Builder->ConfigurarNombre();
		Builder->ConfigurarTipo();
		Builder->ConfigurarDano();
		Builder->ConfigurarAlcance();

		return Resultado;
	}
};
