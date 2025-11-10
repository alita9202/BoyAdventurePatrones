// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RutaPatrulla.generated.h"

UCLASS()
class BOYADVENTUREPATRONES_API ARutaPatrulla : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARutaPatrulla();

	UPROPERTY(EditAnywhere, Category = "Patrulla")
	TArray<AActor*> Puntos;

	int32 NumPuntos() const { return Puntos.Num(); }
	AActor* GetPunto(int32 Index) const { return Puntos.IsValidIndex(Index) ? Puntos[Index] : nullptr; }

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:	
	virtual void OnConstruction(const FTransform& Transform) override;
};
