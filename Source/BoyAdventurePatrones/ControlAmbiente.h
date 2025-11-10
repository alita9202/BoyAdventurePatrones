// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ControlAmbiente.generated.h"

class UTerrenoFactory;
class UDesiertoFactory;
class UBosqueFactory;
class UMaterialInterface;
UCLASS()
class BOYADVENTUREPATRONES_API AControlAmbiente : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AControlAmbiente();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    /** Opcional: actor del piso (StaticMeshActor). Si está vacío, se buscará por etiqueta "Piso". */
    UPROPERTY(EditAnywhere, Category = "Ambiente")
    AActor* ActorPiso;

    /** Materiales para asignar a las fábricas */
    UPROPERTY(EditAnywhere, Category = "Ambiente")
    UMaterialInterface* MaterialSueloDesierto;

    UPROPERTY(EditAnywhere, Category = "Ambiente")
    UMaterialInterface* MaterialSueloBosque;

    /** Número de material a aplicar (índice del elemento del mesh) */
    UPROPERTY(EditAnywhere, Category = "Ambiente", meta = (ClampMin = "0"))
    int32 IndiceMaterial = 0;

    /** Fábrica seleccionada en juego (solo lectura) */
    UPROPERTY(VisibleAnywhere, Category = "Ambiente")
    UTerrenoFactory* FabricaSeleccionada;

private:
    void ElegirFabricaAleatoria();
    void AplicarMaterialAlPiso(UMaterialInterface* Material);
    AActor* BuscarActorPisoPorEtiqueta() const;
};
