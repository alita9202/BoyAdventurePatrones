// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmaBaseBuilder.h"

void UArmaBaseBuilder::CrearNuevaArma(UWorld* World, const FVector& Location, const FRotator& Rotation)
{
	if (!World || !*ClaseArma) { ArmaActual = nullptr; return; }

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ArmaActual = World->SpawnActor<AArmaBase>(ClaseArma, Location, Rotation, SpawnInfo);

}

void UArmaBaseBuilder::ConfigurarNombre()
{
}

void UArmaBaseBuilder::ConfigurarTipo()
{
}

void UArmaBaseBuilder::ConfigurarDano()
{
}

void UArmaBaseBuilder::ConfigurarAlcance()
{
}
