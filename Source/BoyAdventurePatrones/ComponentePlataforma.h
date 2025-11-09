// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ComponentePlataforma.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOYADVENTUREPATRONES_API UComponentePlataforma : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponentePlataforma();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Activa animación de la plataforma (por ejemplo moverla o cambiar color)
	UFUNCTION(BlueprintCallable)
	void ActivarAnimacion();

	// Aplica efecto al jugador (daño, impulso, etc.)
	UFUNCTION(BlueprintCallable)
	void AfectarJugador(AActor* Jugador);
		
};
