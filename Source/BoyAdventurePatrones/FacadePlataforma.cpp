// Fill out your copyright notice in the Description page of Project Settings.

#include "FacadePlataforma.h"
#include "Plataforma.h"
#include "Engine/World.h"
//#include "ConstructorHelpers.h"

// Sets default values
AFacadePlataforma::AFacadePlataforma()
{
	PrimaryActorTick.bCanEverTick = true;

	// Opcional: asignar ClasePlataforma por defecto si no se hace desde el editor
	if (!ClasePlataforma)
	{
		ClasePlataforma = APlataforma::StaticClass();
	}
}

// Called when the game starts or when spawned
void AFacadePlataforma::BeginPlay()
{
	Super::BeginPlay();

	// Asegurarse de que ClasePlataforma tenga un valor válido
	if (!ClasePlataforma)
	{
		ClasePlataforma = APlataforma::StaticClass();
	}

	// Inicializar plataformas
	InicializarPlataformas();
}

// Called every frame
void AFacadePlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFacadePlataforma::InicializarPlataformas()
{
	if (!ClasePlataforma)
	{
		UE_LOG(LogTemp, Error, TEXT("No se asignó ClasePlataforma en FacadePlataforma"));
		return;
	}

	const float DistanciaEntrePlataformas = 300.0f;
	const float AlturaEntrePisos = 200.0f;

	// Coordenada base visible (puedes cambiarla según tu mapa)
	FVector Base = GetActorLocation();
	Base.X = Base.X != 0.f ? Base.X : -950.f;   // usar coordenadas visibles
	Base.Y = Base.Y != 0.f ? Base.Y : -470.f;
	Base.Z = Base.Z != 0.f ? Base.Z : 250.f;    // altura sobre el suelo

	for (int32 Piso = 0; Piso < CantidadPisos; ++Piso)
	{
		for (int32 i = 0; i < PlataformasPorPiso; ++i)
		{
			FVector Posicion = Base;
			Posicion.X += i * DistanciaEntrePlataformas;
			Posicion.Z += Piso * AlturaEntrePisos;

			APlataforma* NuevaPlataforma = GetWorld()->SpawnActor<APlataforma>(ClasePlataforma, Posicion, FRotator::ZeroRotator);
			if (NuevaPlataforma)
			{
				// 🔹 Asignar fase de animación aleatoria para movimiento independiente
				NuevaPlataforma->FaseAnimacion = FMath::RandRange(0.f, PI);

				PlataformasNivel.Add(NuevaPlataforma);
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Se generaron %d plataformas."), PlataformasNivel.Num());
}


void AFacadePlataforma::ActivarAnimacionEnPiso(int32 Piso)
{
	for (APlataforma* Plataforma : PlataformasNivel)
	{
		if (Plataforma)
		{
			Plataforma->ActivarAnimacion();
		}
	}
}

void AFacadePlataforma::AfectarJugadorEnTodas(AActor* Jugador)
{
	for (APlataforma* Plataforma : PlataformasNivel)
	{
		if (Plataforma)
		{
			Plataforma->AfectarJugador(Jugador);
		}
	}
}
