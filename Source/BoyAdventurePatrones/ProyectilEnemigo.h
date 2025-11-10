// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProyectilEnemigo.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class BOYADVENTUREPATRONES_API AProyectilEnemigo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProyectilEnemigo();

	UPROPERTY(VisibleAnywhere, Category = "Proyectil")
	USphereComponent* Colision;

	UPROPERTY(VisibleAnywhere, Category = "Proyectil")
	UProjectileMovementComponent* Movimiento;

	UPROPERTY(EditAnywhere, Category = "Proyectil")
	float VidaSegundos = 3.f;

	void DispararEnDireccion(const FVector& Direccion, float Velocidad);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
