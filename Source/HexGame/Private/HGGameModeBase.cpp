// Copyright Gargowle 2022


#include "HGGameModeBase.h"

AHGGameModeBase::AHGGameModeBase()
{
	BoardWidth = 10;
	BoardHeight = 8;
}

void AHGGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	GenerateTileMap();
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
			
			FVector WorldLocation = AxCoord.ToWorldCoordinate();
			FRotator WorldRotation = FRotator::ZeroRotator;
			WorldRotation.Yaw = 90.0f; // TODO: rotate mesh by 90° in Blender, reimport, and remove this line
			FTransform SpawnTM = FTransform(WorldRotation, WorldLocation);

			AHGTileActor* CurrentTile = GetWorld()->SpawnActor<AHGTileActor>(SpawnClass, SpawnTM, SpawnParams);
			CurrentTile->SetHexCoordinate(AxCoord);

			TileMap.Emplace(AxCoord, CurrentTile);
		}
	}
}
