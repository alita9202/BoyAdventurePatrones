// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentePlataforma.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UComponentePlataforma::UComponentePlataforma()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UComponentePlataforma::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UComponentePlataforma::ActivarAnimacion()
{
	if (AActor* Dueño = GetOwner())
	{
		FVector PosInicial = Dueño->GetActorLocation();
		FVector PosFinal = PosInicial + FVector(0, 0, 80.0f); // sube 80 unidades

		// Subir la plataforma
		Dueño->SetActorLocation(PosFinal);
		UE_LOG(LogTemp, Warning, TEXT("Plataforma %s sube"), *Dueño->GetName());

		// Esperar un momento y luego bajarla
		FTimerHandle Temporizador;
		GetWorld()->GetTimerManager().SetTimer(Temporizador, [Dueño, PosInicial]()
			{
				if (Dueño)
				{
					Dueño->SetActorLocation(PosInicial);
					UE_LOG(LogTemp, Warning, TEXT("Plataforma %s baja"), *Dueño->GetName());
				}
			}, 0.5f, false); // 0.5 segundos después baja
	}
}

void UComponentePlataforma::AfectarJugador(AActor* Jugador)
{
	if (Jugador)
	{
		// Aquí podrías aplicar impulso, daño, etc.
		UE_LOG(LogTemp, Warning, TEXT("Jugador afectado por plataforma: %s"), *Jugador->GetName());
	}
}

// Called every frame
void UComponentePlataforma::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

