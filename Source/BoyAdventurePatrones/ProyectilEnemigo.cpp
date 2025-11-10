// Fill out your copyright notice in the Description page of Project Settings.


#include "ProyectilEnemigo.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProyectilEnemigo::AProyectilEnemigo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    Colision = CreateDefaultSubobject<USphereComponent>(TEXT("Colision"));
    SetRootComponent(Colision);
    Colision->InitSphereRadius(10.f);
    Colision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Colision->SetCollisionResponseToAllChannels(ECR_Overlap);
    Colision->OnComponentBeginOverlap.AddDynamic(this, &AProyectilEnemigo::OnOverlap);

    Movimiento = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movimiento"));
    Movimiento->bRotationFollowsVelocity = true;
    Movimiento->bShouldBounce = false;
    Movimiento->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AProyectilEnemigo::BeginPlay()
{
	Super::BeginPlay();
    SetLifeSpan(VidaSegundos);
}

void AProyectilEnemigo::DispararEnDireccion(const FVector& Direccion, float Velocidad)
{
    if (Movimiento)
    {
        Movimiento->Velocity = Direccion * Velocidad;
    }
}

void AProyectilEnemigo::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Aquí podrías aplicar daño real. Por ahora, solo destruir.
    Destroy();
}

