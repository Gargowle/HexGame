// Copyright Gargowle 2022


#include "HGTileActor.h"

#define Z_POSITION_OFFSET_LIMIT 20.0f

// Sets default values
AHGTileActor::AHGTileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HexMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(TEXT("UI"));
	
	// assume default values
	HexCoord = FAxialCoordinate();
}

FAxialCoordinate AHGTileActor::GetHexCoordinate() const
{
	return HexCoord;
}

void AHGTileActor::SetHexCoordinate(const FAxialCoordinate& HexCoordinate)
{
	HexCoord = HexCoordinate;
	SetActorLocation(HexCoordinate.ToWorldCoordinate() + FVector(0,0, GetRandomZOffset()));
}

// Called when the game starts or when spawned
void AHGTileActor::BeginPlay()
{
	Super::BeginPlay();
}

float AHGTileActor::GetRandomZOffset()
{
	return FMath::RandRange(- Z_POSITION_OFFSET_LIMIT, Z_POSITION_OFFSET_LIMIT);
}

