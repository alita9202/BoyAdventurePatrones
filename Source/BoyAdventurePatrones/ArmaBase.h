// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InformacionArma.h"
#include "ArmaBase.generated.h"

class USphereComponent;
class APublisher;

UCLASS()
class BOYADVENTUREPATRONES_API AArmaBase : public AActor, public IInformacionArma
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArmaBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// === VISUAL ===
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arma|Visual")
	class UStaticMeshComponent* Mesh;

	// === COLISIÓN/OVERLAP ===
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arma|Colision")
	class USphereComponent* Sphere;

	// Datos
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arma")
	FWeaponStats Stats;

	bool bRecolectada = false;

public:	
	// Informará a observadores al iniciar solapamiento
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Permite que el Builder modifique las características sin exponer Stats por completo
	FORCEINLINE FWeaponStats& EditStats() { return Stats; }

	// Interfaz
	virtual FWeaponStats GetWeaponStats_Implementation() const override { return Stats; }
	
	// Ajuste opcional para que el actor “asiente” en el suelo usando la altura del mesh
	UFUNCTION(BlueprintCallable, Category = "Arma|Utils")
	void SnapToGroundZ(float GroundZ);
};
