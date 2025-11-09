// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArmaBase.h"   
#include "ArmaBaseBuilder.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class BOYADVENTUREPATRONES_API UArmaBaseBuilder : public UObject
{
	GENERATED_BODY()
protected:
	// La instancia que este builder está construyendo
	UPROPERTY()
	AArmaBase* ArmaActual = nullptr;

	// Clase a spawnear: por defecto AArmaBase
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Builder")
	TSubclassOf<AArmaBase> ClaseArma = AArmaBase::StaticClass();

public:
	// Crea/Spawnea una nueva arma en el mundo
	UFUNCTION(BlueprintCallable, Category = "Builder")
	virtual void CrearNuevaArma(UWorld* World, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator);

	// Pasos de configuración (virtuales; por defecto no hacen nada)
	virtual void ConfigurarNombre();
	virtual void ConfigurarTipo();
	virtual void ConfigurarDano();
	virtual void ConfigurarAlcance();

	// Devuelve el resultado
	UFUNCTION(BlueprintCallable, Category = "Builder")
	AArmaBase* ObtenerResultado() const { return ArmaActual; }

};
