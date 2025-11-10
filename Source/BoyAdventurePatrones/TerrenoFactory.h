// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TerrenoFactory.generated.h"

/**
 * 
 */

class UMaterialInterface;

UCLASS()
class BOYADVENTUREPATRONES_API UTerrenoFactory : public UObject
{
	GENERATED_BODY()

public:
    /** Devuelve el material de piso para este terreno */
    UFUNCTION(BlueprintCallable, Category = "Terreno")
    virtual UMaterialInterface* ObtenerMaterialPiso() const { return nullptr; }

    /** Devuelve el mensaje a mostrar (p.ej. "Terreno: Desierto") */
    UFUNCTION(BlueprintCallable, Category = "Terreno")
    virtual FText ObtenerMensajeAmbiente() const { return FText::GetEmpty(); }

};
