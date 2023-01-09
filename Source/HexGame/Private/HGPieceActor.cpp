// Copyright Gargowle 2022


#include "HGPieceActor.h"

#include "HGGameModeBase.h"

// Sets default values
AHGPieceActor::AHGPieceActor()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

}


void AHGPieceActor::MovePiece(FAxialCoordinate NewHexCoord)
{
	AHGGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AHGGameModeBase>();
	if(ensure(GameMode))
	{
		AHGTileActor* Tile = GameMode->TileMap[NewHexCoord];
		if(ensure(Tile)) // make sure that a tile of this coordinate exists
		{
			HexCoord = NewHexCoord;
			this->TeleportTo(Tile->GetActorLocation(), Tile->GetActorRotation(), false, true);
		}
	}
}

