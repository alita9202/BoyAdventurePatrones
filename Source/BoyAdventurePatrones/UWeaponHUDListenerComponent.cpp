// Fill out your copyright notice in the Description page of Project Settings.


#include "UWeaponHUDListenerComponent.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UUWeaponHUDListenerComponent::UUWeaponHUDListenerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUWeaponHUDListenerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UUWeaponHUDListenerComponent::OnWeaponFocused_Implementation(const FWeaponStats& Stats)
{
	// Texto amigable del enum
	const FString TipoStr = StaticEnum<EWeaponKind>()->GetValueAsString(Stats.Tipo);

	// Mensaje rápido en pantalla
	if (GEngine)
	{
		const FString Msg = FString::Printf(
			TEXT("Arma: %s | Tipo: %s | Daño: %.0f | Alcance: %.0f | Rareza: %d"),
			*Stats.Nombre, *TipoStr, Stats.Dano, Stats.Alcance, Stats.Rareza
		);
		GEngine->AddOnScreenDebugMessage(/*Key*/-1, /*Tiempo*/3.0f, FColor::Yellow, Msg);
	}

	// (Opcional) Log
	UE_LOG(LogTemp, Log, TEXT("[Observer] %s"), *Stats.Nombre);
}

