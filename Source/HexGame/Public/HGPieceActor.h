// Copyright Gargowle 2022

#pragma once

#include "CoreMinimal.h"
#include "HGTileActor.h"
#include "GameFramework/Actor.h"
#include "HGPieceActor.generated.h"

UCLASS()
class HEXGAME_API AHGPieceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHGPieceActor();

protected:
	virtual void PostInitializeComponents() override;
	
	FAxialCoordinate HexCoord;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	
	UFUNCTION()
	virtual void OnActorClicked(AActor* TouchedActor, FKey ButtonPressed);

public:
	virtual void MovePiece(FAxialCoordinate HexCoord);

};
