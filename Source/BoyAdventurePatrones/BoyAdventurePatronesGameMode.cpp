// Copyright Epic Games, Inc. All Rights Reserved.

#include "BoyAdventurePatronesGameMode.h"
#include "BoyAdventurePatronesCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "FacadePlataforma.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/KismetMathLibrary.h"

// Builders/Director/Arma
#include "ArmaDirector.h"
#include "EspadaBuilder.h"
#include "PistolaBuilder.h"
#include "ArmaBase.h"

ABoyAdventurePatronesGameMode::ABoyAdventurePatronesGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
void ABoyAdventurePatronesGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnArmasAleatorias();
	// 🔸 Si no se asignó la clase desde el editor, usa la predeterminada
	if (!ClaseFacadePlataforma)
	{
		ClaseFacadePlataforma = AFacadePlataforma::StaticClass();
	}

	// 🔸 Crear la fachada en el mundo
	FVector PosicionInicial(-290.f, -470.f, 250.f);
	FRotator RotacionInicial = FRotator::ZeroRotator;

	FacadePlataforma = GetWorld()->SpawnActor<AFacadePlataforma>(ClaseFacadePlataforma, PosicionInicial, RotacionInicial);

	if (FacadePlataforma)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fachada de plataformas creada correctamente."));

		// 🔸 Inicializa las plataformas (se crean automáticamente)
		FacadePlataforma->InicializarPlataformas();

		// 🔸 (Opcional) Activa animación de ejemplo en el piso 1
		FacadePlataforma->ActivarAnimacionEnPiso(1);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No se pudo crear la fachada de plataformas."));
	}
}

FVector ABoyAdventurePatronesGameMode::ObtenerCentroSpawn() const
{
	if (!GetWorld()) return FVector::ZeroVector;

	TArray<AActor*> Starts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Starts);
	if (Starts.Num() > 0 && Starts[0])
	{
		return Starts[0]->GetActorLocation();
	}
	return FVector::ZeroVector;
}

bool ABoyAdventurePatronesGameMode::EsValido(const FVector& Punto, const TArray<FVector>& Usados) const
{
	for (const FVector& U : Usados)
	{
		if (FVector::DistSquared(Punto, U) < FMath::Square(DistanciaMinima))
		{
			return false;
		}
	}
	return true;
}

bool ABoyAdventurePatronesGameMode::EncontrarPuntoAleatorioValido(
	const FVector& Centro,
	FVector& OutPunto,
	const TArray<FVector>& Usados) const
{
	if (!GetWorld()) return false;

	// Parámetros del raycast vertical para “asentar” el arma en el suelo
	const float AlturaRaycast = 800.f;     // qué tan alto lanzamos el rayo
	const float ProfundidadRaycast = 1000.f; // qué tan abajo permitimos caer
	FCollisionQueryParams Params(SCENE_QUERY_STAT(ArmaSpawnTrace), false);
	Params.bTraceComplex = false;
	Params.bReturnPhysicalMaterial = false;

	for (int32 Intento = 0; Intento < MaxIntentosPorArma; ++Intento)
	{
		// 1) Punto aleatorio en un círculo (radio = RadioSpawn) alrededor de Centro
		const float Ang = FMath::FRandRange(0.f, 2.f * PI);
		const float R = FMath::Sqrt(FMath::FRand()) * RadioSpawn; // distribución uniforme en área
		FVector Candidato = Centro + FVector(FMath::Cos(Ang) * R, FMath::Sin(Ang) * R, 0.f);

		// 2) Raycast vertical desde arriba hacia abajo para encontrar el “piso”
		const FVector Origen = Candidato + FVector(0, 0, AlturaRaycast);
		const FVector Fin = Candidato - FVector(0, 0, ProfundidadRaycast);

		FHitResult Hit;
		// Usa el canal que mejor te funcione en tu nivel: WorldStatic / Visibility
		const ECollisionChannel Canal = ECollisionChannel::ECC_Visibility;

		bool bGolpeo = GetWorld()->LineTraceSingleByChannel(Hit, Origen, Fin, Canal, Params);

		if (bGolpeo)
		{
			// Ajusta Z al impacto para que el arma repose sobre la superficie
			Candidato.Z = Hit.ImpactPoint.Z + 2.f; // leve offset para evitar clipping
		}
		// Si no golpeó nada, se deja el Z original; si quieres, puedes forzar un Z fijo:
		// else { Candidato.Z = Centro.Z; }

		// 3) Revisa distancia mínima con lo ya colocado
		if (EsValido(Candidato, Usados))
		{
			OutPunto = Candidato;
			return true;
		}
	}

	return false;
}


void ABoyAdventurePatronesGameMode::SpawnArmasAleatorias()
{
	if (!GetWorld() || NumArmas <= 0) return;

	UArmaDirector* Director = NewObject<UArmaDirector>(this);
	if (!Director) return;

	const FVector Centro = ObtenerCentroSpawn();
	TArray<FVector> PuntosUsados;
	PuntosUsados.Reserve(NumArmas);

	for (int32 i = 0; i < NumArmas; ++i)
	{
		FVector Punto;
		if (!EncontrarPuntoAleatorioValido(Centro, Punto, PuntosUsados))
		{
			continue; // no se halló un punto válido para esta iteración
		}

		// Elegir builder al azar
		const bool bEsEspada = FMath::RandBool();
		UArmaBaseBuilder* Builder = bEsEspada
			? static_cast<UArmaBaseBuilder*>(NewObject<UEspadaBuilder>(this))
			: static_cast<UArmaBaseBuilder*>(NewObject<UPistolaBuilder>(this));

		if (!Builder) continue;

		AArmaBase* Arma = Director->Construir(GetWorld(), Builder, Punto);
		if (Arma)
		{
			PuntosUsados.Add(Punto);

#if WITH_EDITOR
			const FString TipoStr = bEsEspada ? TEXT("Espada") : TEXT("Pistola");
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1, 2.f, FColor::Cyan,
					FString::Printf(TEXT("Spawn: %s en %s"), *TipoStr, *Punto.ToString())
				);
			}
#endif
		}
	}
}

void ABoyAdventurePatronesGameMode::ActivarAnimacionPiso(int32 Piso)
{
	if (FacadePlataforma)
	{
		FacadePlataforma->ActivarAnimacionEnPiso(Piso);
	}
}

void ABoyAdventurePatronesGameMode::AfectarJugadorEnPlataformas(AActor* Jugador)
{
	if (FacadePlataforma)
	{
		FacadePlataforma->AfectarJugadorEnTodas(Jugador);
	}
}
