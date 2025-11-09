// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FacadePlataforma.generated.h"

class APlataforma;

UCLASS()
class BOYADVENTUREPATRONES_API AFacadePlataforma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFacadePlataforma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Configuración
	UPROPERTY(EditAnywhere, Category = "Configuración")
	int32 CantidadPisos = 4;

	UPROPERTY(EditAnywhere, Category = "Configuración")
	int32 PlataformasPorPiso = 4;

	UPROPERTY(EditAnywhere, Category = "Configuración")
	TSubclassOf<APlataforma> ClasePlataforma;

	// Arreglo de todas las plataformas creadas
	UPROPERTY(VisibleAnywhere, Category = "Datos")
	TArray<APlataforma*> PlataformasNivel;

	UPROPERTY(EditAnywhere, Category = "Animación")
	float FaseAnimacion;

	// Crea todas las plataformas automáticamente
	UFUNCTION(BlueprintCallable)
	void InicializarPlataformas();

	// Activa animación de todas las plataformas de un piso
	UFUNCTION(BlueprintCallable)
	void ActivarAnimacionEnPiso(int32 Piso);

	// Aplica efecto al jugador en todas las plataformas
	UFUNCTION(BlueprintCallable)
	void AfectarJugadorEnTodas(AActor* Jugador);
};
