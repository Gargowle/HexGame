// Copyright Gargowle 2022


#include "HGPieceActor.h"

#include "HGGameModeBase.h"

// Sets default values
AHGPieceActor::AHGPieceActor()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(TEXT("UI"));

}

void AHGPieceActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnClicked.AddUniqueDynamic(this, &AHGPieceActor::OnActorClicked);
}

void AHGPieceActor::OnActorClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	AHGGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AHGGameModeBase>();
	if(ensure(GameMode))
	{
		GameMode->SetActivePiece(this);
	}
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

TArray<FAxialCoordinate> AHGPieceActor::GetPossibleMoveLocations_Implementation()
{
	TArray<FAxialCoordinate> PossibleMoveLocations;

	// when not overridden in a BP, return all fields by default
	AHGGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AHGGameModeBase>();
	if(ensure(GameMode))
	{
		for(int32 Row = 0; Row < GameMode->BoardHeight; ++Row)
		{
			for(int32 Column = 0; Column < GameMode->BoardWidth; ++Column)
			{
				auto Coord = FAxialCoordinate::HexFromIndex(Row, Column);
				if(GameMode->TileMap[Coord]->CanAcceptNewPiece())
				{
					PossibleMoveLocations.Emplace(FAxialCoordinate::HexFromIndex(Row, Column));
				}
			}
		}
	}

	return PossibleMoveLocations;
}

