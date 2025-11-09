// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArmaObserver.h"
#include "UWeaponHUDListenerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOYADVENTUREPATRONES_API UUWeaponHUDListenerComponent : public UActorComponent, public IArmaObserver
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUWeaponHUDListenerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Implementación del callback del Observer
	virtual void OnWeaponFocused_Implementation(const FWeaponStats& Stats) override;

};
