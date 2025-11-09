// Fill out your copyright notice in the Description page of Project Settings.


#include "PistolaBuilder.h"
#include "InformacionArma.h"


void UPistolaBuilder::ConfigurarNombre()
{
	if (ArmaActual)
	{
		ArmaActual->EditStats().Nombre = TEXT("Pistola de Fuego Rápido");
	}
}
void UPistolaBuilder::ConfigurarTipo()
{
	if (ArmaActual)
	{
		ArmaActual->EditStats().Tipo = EWeaponKind::Pistola;
	}
}
void UPistolaBuilder::ConfigurarDano()
{
	if (ArmaActual)
	{
		ArmaActual->EditStats().Dano = 35.f; // ejemplo
	}
}
void UPistolaBuilder::ConfigurarAlcance()
{
	if (ArmaActual)
	{
		ArmaActual->EditStats().Alcance = 1000.f; // alcance medio
	}
}

