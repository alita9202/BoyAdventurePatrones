// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlAmbiente.h"
#include "DesiertoFactory.h"
#include "BosqueFactory.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AControlAmbiente::AControlAmbiente()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorPiso = nullptr;
	MaterialSueloDesierto = nullptr;
	MaterialSueloBosque = nullptr;
	FabricaSeleccionada = nullptr;
}

// Called when the game starts or when spawned
void AControlAmbiente::BeginPlay()
{
	Super::BeginPlay();

    ElegirFabricaAleatoria();

    if (!FabricaSeleccionada)
    {
        UE_LOG(LogTemp, Warning, TEXT("ControlAmbiente: No se pudo seleccionar una fábrica."));
        return;
    }

    UMaterialInterface* Material = FabricaSeleccionada->ObtenerMaterialPiso();
    AplicarMaterialAlPiso(Material);

    const FText Msg = FabricaSeleccionada->ObtenerMensajeAmbiente();
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, Msg.ToString());
    }
}

void AControlAmbiente::ElegirFabricaAleatoria()
{
    const bool bDesierto = FMath::RandBool();

    if (bDesierto)
    {
        UDesiertoFactory* Des = NewObject<UDesiertoFactory>(this);
        if (Des)
        {
            Des->MaterialDesierto = MaterialSueloDesierto;
            FabricaSeleccionada = Des;
        }
    }
    else
    {
        UBosqueFactory* Bos = NewObject<UBosqueFactory>(this);
        if (Bos)
        {
            Bos->MaterialBosque = MaterialSueloBosque;
            FabricaSeleccionada = Bos;
        }
    }
}

void AControlAmbiente::AplicarMaterialAlPiso(UMaterialInterface* Material)
{
    if (!Material) return;

    AActor* Piso = ActorPiso ? ActorPiso : BuscarActorPisoPorEtiqueta();
    if (!Piso) return;

    // Intentar obtener StaticMeshComponent
    UStaticMeshComponent* SMC = Piso->FindComponentByClass<UStaticMeshComponent>();
    if (!SMC)
    {
        // Si es un StaticMeshActor, tomar su componente
        if (AStaticMeshActor* SMA = Cast<AStaticMeshActor>(Piso))
        {
            SMC = SMA->GetStaticMeshComponent();
        }
    }
    if (!SMC) return;

    const int32 NumElems = SMC->GetNumMaterials();
    const int32 Index = FMath::Clamp(IndiceMaterial, 0, FMath::Max(0, NumElems - 1));
    SMC->SetMaterial(Index, Material);
}

AActor* AControlAmbiente::BuscarActorPisoPorEtiqueta() const
{
    TArray<AActor*> Todos;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Piso")), Todos);
    return Todos.Num() > 0 ? Todos[0] : nullptr;
}

