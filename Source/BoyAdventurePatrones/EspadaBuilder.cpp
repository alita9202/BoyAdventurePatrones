// Fill out your copyright notice in the Description page of Project Settings.


#include "EspadaBuilder.h"
#include "InformacionArma.h"

void UEspadaBuilder::ConfigurarNombre()
{
	if (ArmaActual)
	{
		ArmaActual->EditStats().Nombre = TEXT("Espada Legendaria");
	}
}

void UEspadaBuilder::ConfigurarTipo()
{
	if (ArmaActual)
	{
		ArmaActual->EditStats().Tipo = EWeaponKind::Espada;
	}
}

void UEspadaBuilder::ConfigurarDano()
{
	if (ArmaActual)
	{
		ArmaActual->EditStats().Dano = 75.f; // ejemplo
	}
}

void UEspadaBuilder::ConfigurarAlcance()
{
	if (ArmaActual)
	{
		ArmaActual->EditStats().Alcance = 150.f; // cuerpo a cuerpo extendido
	}
}
