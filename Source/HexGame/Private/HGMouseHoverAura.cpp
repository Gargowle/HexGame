// Copyright Gargowle 2022


#include "HGMouseHoverAura.h"

// Sets default values
AHGMouseHoverAura::AHGMouseHoverAura()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	MeshComponent->SetVisibility(false, true);
}

void AHGMouseHoverAura::SetVisibility(bool bNewVisibility)
{
	MeshComponent->SetVisibility(bNewVisibility, true);
}

