// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InformacionArma.h"
#include "ArmaObserver.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,Blueprintable)
class UArmaObserver : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOYADVENTUREPATRONES_API IArmaObserver
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/** Recibirá notificación cuando el jugador enfoque/toque un arma */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Arma|Observer")
	void OnWeaponFocused(const FWeaponStats& Stats);
};
