// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plataforma.generated.h"

class UComponentePlataforma;
class UStaticMeshComponent;

UCLASS()
class BOYADVENTUREPATRONES_API APlataforma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlataforma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Componente raíz (puede ser un mesh simple)
	UPROPERTY(VisibleAnywhere, Category = "Componentes")
	UStaticMeshComponent* MallaPlataforma;

	// Estado de animación
	UPROPERTY(VisibleAnywhere, Category = "Animación")
	bool bAnimacionActiva;

	// Configuración del movimiento
	UPROPERTY(EditAnywhere, Category = "Animación")
	float AmplitudMovimiento;

	UPROPERTY(EditAnywhere, Category = "Animación")
	float VelocidadMovimiento;

	UPROPERTY(EditAnywhere, Category = "Animación")
	float FaseAnimacion; // valor en radianes

	// Posición inicial guardada
	FVector PosicionInicial;

	// Activar animación suave
	void ActivarAnimacion();

	// Desactivar animación
	void DesactivarAnimacion();

	// Aplica un efecto simple al jugador (por ejemplo, un impulso o daño)
	UFUNCTION(BlueprintCallable, Category = "Acciones")
	void AfectarJugador(AActor* Jugador);

};
