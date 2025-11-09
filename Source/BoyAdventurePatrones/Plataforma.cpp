// Fill out your copyright notice in the Description page of Project Settings.


#include "Plataforma.h"
#include "Components/StaticMeshComponent.h"
#include "ComponentePlataforma.h"
#include "Engine/World.h"


// Sets default values
APlataforma::APlataforma()
{
	PrimaryActorTick.bCanEverTick = true;

	MallaPlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaPlataforma"));
	RootComponent = MallaPlataforma;

	// Asignar un mesh del StarterContent
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (Mesh.Succeeded())
	{
		MallaPlataforma->SetStaticMesh(Mesh.Object);
		MallaPlataforma->SetWorldScale3D(FVector(2.f, 2.f, 0.5f)); // tamaño de la plataforma
	}

	bAnimacionActiva = false;
	AmplitudMovimiento = 100.f;
	VelocidadMovimiento = 2.f;
}


// Called when the game starts or when spawned
void APlataforma::BeginPlay()
{
	Super::BeginPlay();
	// Guardamos la posición inicial
	PosicionInicial = GetActorLocation();

}

// Called every frame
void APlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAnimacionActiva)
	{
		// Movimiento suave tipo seno (rebote vertical)
		float Desplazamiento = FMath::Sin(GetWorld()->GetTimeSeconds() * VelocidadMovimiento + FaseAnimacion) * AmplitudMovimiento;
		//toda la plataforma sube y baja
		//float Desplazamiento = FMath::Sin(GetWorld()->GetTimeSeconds() * VelocidadMovimiento) * AmplitudMovimiento;
		FVector NuevaPos = PosicionInicial;
		NuevaPos.Z += Desplazamiento;
		SetActorLocation(NuevaPos);
	}
}

void APlataforma::ActivarAnimacion()
{
	bAnimacionActiva = true;
	UE_LOG(LogTemp, Warning, TEXT("Animación activada en %s"), *GetName());
}

void APlataforma::DesactivarAnimacion()
{
	bAnimacionActiva = false;
	// Regresa suavemente a su posición inicial
	SetActorLocation(PosicionInicial);
	UE_LOG(LogTemp, Warning, TEXT("Animación desactivada en %s"), *GetName());
}

void APlataforma::AfectarJugador(AActor* Jugador)
{
	if (!Jugador) return;

	// Aquí puedes aplicar un impulso, daño o cualquier efecto.
	// Por ahora haremos un ejemplo simple: mover al jugador un poco hacia arriba.

	FVector NuevaPos = Jugador->GetActorLocation();
	NuevaPos.Z += 100.f; // Eleva ligeramente al jugador
	Jugador->SetActorLocation(NuevaPos);

	UE_LOG(LogTemp, Warning, TEXT("%s fue afectado por la plataforma %s"), *Jugador->GetName(), *GetName());
}

