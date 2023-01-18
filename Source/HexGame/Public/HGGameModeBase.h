// Copyright Gargowle 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HGTileActor.h"
#include "HGMouseHoverAura.h"
#include "HGPieceActor.h"
#include "HGGameModeBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class HEXGAME_API AHGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AHGTileActor> SpawnClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AHGMouseHoverAura> MouseHoverAuraClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AHGPieceActor> PieceActorClass;


public:
	AHGGameModeBase();
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UPROPERTY(BlueprintReadWrite)
	AHGMouseHoverAura* MouseHoverAuraActor;
		
	UPROPERTY()
	TMap<FAxialCoordinate, AHGTileActor*> TileMap;

	UPROPERTY()
	TArray<AHGPieceActor*> Pieces;

	UPROPERTY()
	AHGPieceActor* ActivePiece;

	void GenerateTileMap();

	UPROPERTY(EditDefaultsOnly)
	int32 BoardWidth;

	UPROPERTY(EditDefaultsOnly)
	int32 BoardHeight;

	void SetActivePiece(AHGPieceActor* NewActivePiece);

	void ReCalculateReachableTiles();
};
