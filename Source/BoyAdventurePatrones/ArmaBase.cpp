// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmaBase.h"
#include "Components/SphereComponent.h"
#include "Publisher.h"
#include "ArmaObserver.h"
#include "Engine/Engine.h"
#include "BoyAdventurePatronesCharacter.h"
// Sets default values
AArmaBase::AArmaBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Colisión simple para overlap
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Sphere->InitSphereRadius(60.f);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionObjectType(ECC_WorldDynamic);
	Sphere->SetCollisionResponseToAllChannels(ECR_Overlap);

	// Malla visible
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // solo la esfera hace overlap
	Mesh->SetRelativeScale3D(FVector(1.f));

	// Cargar una malla básica del Engine (se verá siempre aunque no tengas una propia)
	// Puedes cambiar "Cone" por "Cylinder", "Cube", etc.
	// Cargar tu propio asset
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/ThirdPerson/Meshes/futuristic-sci-fi-glock/source/ASM_-_PBR_Metallic_Roughness.ASM_-_PBR_Metallic_Roughness'"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);

		// Ajusta la altura si queda flotando o enterrado
		Mesh->SetRelativeLocation(FVector(0, 0, 0.f)); // prueba con valores entre -20 y +50
		Mesh->SetRelativeScale3D(FVector(0.30f));       // cambia tamaño si es muy grande/pequeño
	}
}

// Called when the game starts or when spawned
void AArmaBase::BeginPlay()
{
	Super::BeginPlay();
}

void AArmaBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (bRecolectada || !OtherActor || OtherActor == this) return;

	// Marcar para evitar dobles llamadas
	bRecolectada = true;

	// 1) Notificar a observadores (actor y sus componentes)
	if (OtherActor->GetClass()->ImplementsInterface(UArmaObserver::StaticClass()))
	{
		IArmaObserver::Execute_OnWeaponFocused(OtherActor, GetWeaponStats_Implementation());
	}
	TArray<UActorComponent*> Components;
	OtherActor->GetComponents(Components);
	for (UActorComponent* Comp : Components)
	{
		if (Comp && Comp->GetClass()->ImplementsInterface(UArmaObserver::StaticClass()))
		{
			IArmaObserver::Execute_OnWeaponFocused(Comp, GetWeaponStats_Implementation());
		}
	}

	// 2) Mensajes de pantalla sobre qué arma se recolectó y que desaparecerá
	if (GEngine)
	{
		const FString TipoStr = StaticEnum<EWeaponKind>()->GetValueAsString(Stats.Tipo);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green,
			FString::Printf(TEXT("Tocada: %s (%s)"), *Stats.Nombre, *TipoStr));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
			FString::Printf(TEXT("Desaparecerá: %s"), *Stats.Nombre));
	}

	// 3) Desactivar colisión y destruir
	SetActorEnableCollision(false);
	// pequeña demora opcional para que el mensaje aparezca un frame
	Destroy();
}

void AArmaBase::SnapToGroundZ(float GroundZ)
{
	// Si tu raycast te dio la Z del piso, sube el actor la “media altura” del mesh
	// Intento genérico usando el bound del componente con su escala actual
	const FBoxSphereBounds B = Mesh->Bounds;                 // en world-space si ya está registrado
	const float HalfHeight = B.BoxExtent.Z;                  // mitad de la altura
	FVector Loc = GetActorLocation();
	Loc.Z = GroundZ + HalfHeight + 1.f;                      // +1 para evitar parpadeo
	SetActorLocation(Loc, false, nullptr, ETeleportType::TeleportPhysics);

}
