// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InformacionArma.generated.h"
// --- Tipo y datos del arma (todo en este header para no crear más archivos) ---

UENUM(BlueprintType)
enum class EWeaponKind : uint8
{
	Espada      UMETA(DisplayName = "Espada"),
	Pistola     UMETA(DisplayName = "Pistola"),
	Arco        UMETA(DisplayName = "Arco"),
	Escopeta    UMETA(DisplayName = "Escopeta"),
	Desconocida UMETA(DisplayName = "Desconocida")
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arma")
	FString Nombre = TEXT("Arma sin nombre");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arma")
	EWeaponKind Tipo = EWeaponKind::Desconocida;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arma")
	float Dano = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arma")
	float Alcance = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arma")
	int32 Rareza = 1; // 1: común, 5: mítico
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInformacionArma : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOYADVENTUREPATRONES_API IInformacionArma
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/** Entregará las características actuales del arma */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Arma|Info")
	FWeaponStats GetWeaponStats() const;
};
