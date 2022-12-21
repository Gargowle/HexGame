// Copyright Gargowle 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGTileActor.generated.h"

/* Axial coordinates as explained here: https://www.redblobgames.com/grids/hexagons/#coordinates */
USTRUCT()
struct FAxialCoordinate
{
	GENERATED_BODY()
	
private:
	int32 q_;
	int32 r_;

public:
	FAxialCoordinate(): q_(0), r_(0) {}
	FAxialCoordinate(int q_in, int r_in): q_(q_in), r_(r_in) {}

	int32 q() const { return q_;}
	int32 r() const { return r_;}
	int32 s() const { return - q_ - r_;}

	// operator needs to be defined for the AxialCoordinate type to be used as key in TMap
	bool operator==(const FAxialCoordinate& Other) const
	{
		return (q_ == Other.q_) && (r_ == Other.r_);
	}
};

// function needs to be defined for the AxialCoordinate type to be used as key in TMap
FORCEINLINE uint32 GetTypeHash(const FAxialCoordinate& Coord)
{
	return FCrc::MemCrc_DEPRECATED(&Coord, sizeof(FAxialCoordinate));
}

// vectors that the axes in the axial ("hex") coordinate system correspond to in world coordinates
const FVector BaseVectorQ = HEX_DIAMETER * FVector(sqrt(3.0f), 0.0f, 0.0f);
const FVector BaseVectorR = HEX_DIAMETER * FVector(sqrt(3.0f)/2.0f, 1.5f, 0.0f);
const FVector BaseVectorS = -BaseVectorQ - BaseVectorR;

// vectors (q,r) that the world coordinate axes correspond to in in the axial ("hex") coordinate system 
const FVector2D BaseVectorX = FVector2D(sqrt(3.0f)/3.0f, 0) / HEX_DIAMETER;
const FVector2D BaseVectorY = FVector2D(-1.0f/3.0f, 2.0f/3.0f) / HEX_DIAMETER;


UCLASS()
class HEXGAME_API AHGTileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHGTileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
