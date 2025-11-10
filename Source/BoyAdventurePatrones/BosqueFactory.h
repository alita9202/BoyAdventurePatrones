// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TerrenoFactory.h"
#include "BosqueFactory.generated.h"

/**
 * 
 */
class UMaterialInterface;

UCLASS()
class BOYADVENTUREPATRONES_API UBosqueFactory : public UTerrenoFactory
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Terreno")
    UMaterialInterface* MaterialBosque = nullptr;

    virtual UMaterialInterface* ObtenerMaterialPiso() const override { return MaterialBosque; }
    virtual FText ObtenerMensajeAmbiente() const override { return FText::FromString(TEXT("Terreno: Bosque")); }

};
