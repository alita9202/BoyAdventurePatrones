// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoBase.h"
#include "EnemyState_Patrulla.h"
#include "EnemyState_Ataque.h"
#include "AttackStrategy.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "ControlIAEnemigo.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemigoBase::AEnemigoBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // ---- VISUAL BÁSICO PARA VER AL ENEMIGO ----
    Visual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
    Visual->SetupAttachment(GetRootComponent());
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (MeshAsset.Succeeded())
    {
        Visual->SetStaticMesh(MeshAsset.Object);
        Visual->SetRelativeLocation(FVector(0.f, 0.f, 40.f));   // súbelo un poco
        Visual->SetWorldScale3D(FVector(0.6f));                 // tamaño amigable
    }
    Visual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Visual->SetHiddenInGame(false);

    
    // Componente de detección
    DeteccionJugador = CreateDefaultSubobject<USphereComponent>(TEXT("DeteccionJugador"));
    DeteccionJugador->SetupAttachment(GetRootComponent());
    DeteccionJugador->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    DeteccionJugador->SetCollisionObjectType(ECC_WorldDynamic);
    DeteccionJugador->SetCollisionResponseToAllChannels(ECR_Overlap);

    RadioDeteccion = 600.f;
    VelocidadMovimiento = 300.f;

    // IA
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AControlIAEnemigo::StaticClass();

    ObjetivoJugador = nullptr;
    EstadoActual = nullptr;
    EstrategiaAtaque = nullptr;
    RutaAsignada = nullptr;
}

// Called when the game starts or when spawned
void AEnemigoBase::BeginPlay()
{
	Super::BeginPlay();
    // Aplicar radio al componente
    if (DeteccionJugador)
    {
        DeteccionJugador->SetSphereRadius(RadioDeteccion);
    }

    // Velocidad movimiento
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = VelocidadMovimiento;
    }

    // Buscar jugador
    APawn* PawnJugador = UGameplayStatics::GetPlayerPawn(this, 0);
    ObjetivoJugador = PawnJugador;

    // Estado inicial => Patrulla
    CambiarAEstadoPatrulla();
}

// Called every frame
void AEnemigoBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

#if WITH_EDITOR
    // Visualiza el radio de detección en juego
    //DrawDebugSphere(GetWorld(), GetActorLocation(), RadioDeteccion, 16, FColor::Yellow, false, -1.f, 0, 1.5f);
#endif

    if (EstadoActual)
    {
        EstadoActual->Tick(this, DeltaSeconds);
    }
}

void AEnemigoBase::CambiarEstado(UEnemyState* Nuevo)
{
    if (EstadoActual)
    {
        EstadoActual->Exit(this);
    }
    EstadoActual = Nuevo;
    if (EstadoActual)
    {
        EstadoActual->Enter(this);
    }
}

void AEnemigoBase::CambiarAEstadoPatrulla()
{
    UE_LOG(LogTemp, Warning, TEXT("[Enemigo] Cambiando a PATRULLA"));

    // Detener movimiento y limpiar foco
    if (AAIController* AI = Cast<AAIController>(GetController()))
    {
        AI->StopMovement();
        AI->ClearFocus(EAIFocusPriority::Gameplay);
    }

    UEnemyState_Patrulla* Pat = NewObject<UEnemyState_Patrulla>(this);
    CambiarEstado(Pat);
}

void AEnemigoBase::CambiarAEstadoAtaque()
{
    UE_LOG(LogTemp, Warning, TEXT("[Enemigo] Cambiando a ATAQUE"));

    UEnemyState_Ataque* Atk = NewObject<UEnemyState_Ataque>(this);
    CambiarEstado(Atk);
}

void AEnemigoBase::EjecutarAtaque()
{
    if (EstrategiaAtaque)
    {
        EstrategiaAtaque->Execute(this);
    }
}

bool AEnemigoBase::HaLlegadoAlDestino(float ToleranciaPlano) const
{
    // Chequeo básico usando el AIController (si no hay uno, devolvemos false)
    const AAIController* AI = Cast<AAIController>(GetController());
    if (!AI) return false;

    // Alternativa simple: considerar que si no está moviéndose y velocidad muy baja, llegó.
    const FVector Vel = GetVelocity();
    return Vel.Size2D() < 5.f; // muy simple, suficiente para este demo
}

float AEnemigoBase::DistanciaAlJugador() const
{
    if (!ObjetivoJugador) return TNumericLimits<float>::Max();
    return FVector::Dist(GetActorLocation(), ObjetivoJugador->GetActorLocation());
}

// Called to bind functionality to input
void AEnemigoBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

