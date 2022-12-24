// Copyright Gargowle 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HGTileActor.h"
#include "HGGameModeBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class HEXGAME_API AHGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AHGGameModeBase();
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

public:
	UPROPERTY()
	TMap<FAxialCoordinate, AHGTileActor*> TileMap;

	void GenerateTileMap();

	UPROPERTY(EditDefaultsOnly)
	int32 BoardWidth;

	UPROPERTY(EditDefaultsOnly)
	int32 BoardHeight;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AHGTileActor> SpawnClass;
	
};
