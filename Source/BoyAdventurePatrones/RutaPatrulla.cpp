// Fill out your copyright notice in the Description page of Project Settings.


#include "RutaPatrulla.h"
#include "DrawDebugHelpers.h"

// Sets default values
ARutaPatrulla::ARutaPatrulla()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ARutaPatrulla::OnConstruction(const FTransform& Transform)
{
#if WITH_EDITOR
    // Dibujo simple para ver la ruta en el editor/juego
    for (int32 i = 0; i < Puntos.Num(); ++i)
    {
        if (!Puntos[i]) continue;
        const FVector A = GetActorLocation();
        const FVector B = Puntos[i]->GetActorLocation();
        DrawDebugSphere(GetWorld(), B, 20.f, 12, FColor::Green, false, 2.f);
        if (i > 0 && Puntos[i - 1])
        {
            DrawDebugLine(GetWorld(), Puntos[i - 1]->GetActorLocation(), B, FColor::Cyan, false, 2.f, 0, 2.f);
        }
    }
#endif
}

#if WITH_EDITOR
void ARutaPatrulla::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    OnConstruction(GetActorTransform());
}
#endif

