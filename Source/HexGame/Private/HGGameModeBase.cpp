// Copyright Gargowle 2022


#include "HGGameModeBase.h"

#include "HGPawn.h"

AHGGameModeBase::AHGGameModeBase()
{
	BoardWidth = 10;
	BoardHeight = 8;

	DefaultPawnClass = AHGPawn::StaticClass();

	ActivePiece = nullptr;
}

void AHGGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	GenerateTileMap();

	// create the actor that is used to highlight the tile that the player is going to click on
	MouseHoverAuraActor = GetWorld()->SpawnActor<AHGMouseHoverAura>(MouseHoverAuraClass, FTransform::Identity);

	AHGPieceActor* Piece = nullptr;
	for(int32 Row = 0; Row < BoardHeight; ++Row)
	{
		Piece = GetWorld()->SpawnActor<AHGPieceActor>(PieceActorClass, FTransform::Identity);
		Piece->MovePiece(FAxialCoordinate::HexFromIndex(Row, 0));
		Pieces.Push(Piece);
	}
}

void AHGGameModeBase::GenerateTileMap()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	for(int32 Row = 0; Row < BoardHeight; ++Row)
	{
		for(int32 Column = 0; Column < BoardWidth; ++Column)
		{
			FAxialCoordinate AxCoord = FAxialCoordinate::HexFromIndex(Row, Column);
			
			FTransform SpawnTM = FTransform(FRotator::ZeroRotator, AxCoord.ToWorldCoordinate());

			AHGTileActor* CurrentTile = GetWorld()->SpawnActor<AHGTileActor>(SpawnClass, SpawnTM, SpawnParams);
			CurrentTile->SetHexCoordinate(AxCoord);

			TileMap.Emplace(AxCoord, CurrentTile);
		}
	}
}

void AHGGameModeBase::SetActivePiece(AHGPieceActor* NewActivePiece)
{
	if(ensure(IsValid(NewActivePiece)))
	{
		ActivePiece = NewActivePiece;
	}
}
