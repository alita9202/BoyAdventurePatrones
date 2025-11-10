// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TerrenoFactory.h"
#include "DesiertoFactory.generated.h"

/**
 * 
 */
class UMaterialInterface;

UCLASS()
class BOYADVENTUREPATRONES_API UDesiertoFactory : public UTerrenoFactory
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Terreno")
    UMaterialInterface* MaterialDesierto = nullptr;

    virtual UMaterialInterface* ObtenerMaterialPiso() const override { return MaterialDesierto; }
    virtual FText ObtenerMensajeAmbiente() const override { return FText::FromString(TEXT("Terreno: Desierto")); }

};
