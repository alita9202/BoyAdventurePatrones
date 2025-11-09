// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArmaBaseBuilder.h"
#include "PistolaBuilder.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BOYADVENTUREPATRONES_API UPistolaBuilder : public UArmaBaseBuilder
{
	GENERATED_BODY()
public:
	virtual void ConfigurarNombre()  override;
	virtual void ConfigurarTipo()    override;
	virtual void ConfigurarDano()    override;
	virtual void ConfigurarAlcance() override;
};
