// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmaSpawnManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ArmaDirector.h"
#include "EspadaBuilder.h"
#include "PistolaBuilder.h"
#include "Engine/World.h"
#include "BoyAdventurePatronesGameMode.h"

// Sets default values
AArmaSpawnManager::AArmaSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;
	SpawnArea->SetBoxExtent(FVector(1000.f, 1000.f, 200.f));
	SpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AArmaSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	if (!GetWorld()) return;

	UArmaDirector* Director = NewObject<UArmaDirector>(this);

	TArray<FVector> PuntosUsados;
	PuntosUsados.Reserve(NumArmas);

	for (int32 i = 0; i < NumArmas; ++i)
	{
		// Hallar un punto válido
		FVector Punto;
		bool bOk = false;
		for (int32 intento = 0; intento < MaxIntentosPorArma; ++intento)
		{
			Punto = GetRandomPointInBox();
			if (EsValido(Punto, PuntosUsados))
			{
				bOk = true; break;
			}
		}
		if (!bOk) continue;

		// Elegir aleatoriamente el tipo de arma
		const bool bEsEspada = FMath::RandBool();

		UArmaBaseBuilder* Builder = nullptr;
		if (bEsEspada)
		{
			Builder = NewObject<UEspadaBuilder>(this);
		}
		else
		{
			Builder = NewObject<UPistolaBuilder>(this);
		}

		// Construir arma
		if (Director && Builder)
		{
			AArmaBase* Arma = Director->Construir(GetWorld(), Builder, Punto);
			if (Arma)
			{
				PuntosUsados.Add(Punto);
			}
		}
	}
}

FVector AArmaSpawnManager::GetRandomPointInBox() const
{
	const FBoxSphereBounds B = SpawnArea->CalcBounds(SpawnArea->GetComponentTransform());
	const FVector Origin = B.Origin;
	const FVector Extent = SpawnArea->GetUnscaledBoxExtent();

	return UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
}

bool AArmaSpawnManager::EsValido(const FVector& Punto, const TArray<FVector>& Usados) const
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

