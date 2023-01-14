// Copyright Gargowle 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGTileActor.generated.h"

class AHGPieceActor;

// size as present in the mesh
#define HEX_DIAMETER 100.0f


namespace BaseVector
{
	// vectors that the axes in the axial ("hex") coordinate system correspond to in world coordinates
	const FVector Q = HEX_DIAMETER * FVector(sqrt(3.0f), 0.0f, 0.0f);
	const FVector R = HEX_DIAMETER * FVector(sqrt(3.0f)/2.0f, 1.5f, 0.0f);
	const FVector S = -Q - R;

	// vectors (q,r) that the world coordinate axes correspond to in in the axial ("hex") coordinate system 
	const FVector2D X = FVector2D(sqrt(3.0f)/3.0f, 0) / HEX_DIAMETER;
	const FVector2D Y = FVector2D(-1.0f/3.0f, 2.0f/3.0f) / HEX_DIAMETER;
	
}


/* Axial coordinates as explained here: https://www.redblobgames.com/grids/hexagons/#coordinates */
USTRUCT(BlueprintType)
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

	// convenience functions
	FVector ToWorldCoordinate() const
	{
		return BaseVector::Q * q() + BaseVector::R * r();
	}

	static FAxialCoordinate HexFromIndex(int32 Row, int32 Column)
	{
		// bitwise and &1 instead of modulo %2 because it works with negative numbers, too
		int32 q = Column - (Row + (Row & 1)) / 2;
		int32 r = Row;

		return FAxialCoordinate(q, r);		
	};
};

// function needs to be defined for the AxialCoordinate type to be used as key in TMap
FORCEINLINE uint32 GetTypeHash(const FAxialCoordinate& Coord)
{
	return FCrc::MemCrc_DEPRECATED(&Coord, sizeof(FAxialCoordinate));
}


UCLASS(Abstract)
class HEXGAME_API AHGTileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHGTileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual float GetRandomZOffset();

	FAxialCoordinate HexCoord;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WalkableAuraMeshComponent;

	UPROPERTY(BlueprintReadWrite)
	AHGPieceActor* PieceOnTop;

	bool bCanBeReached;
	
	UFUNCTION()
	virtual void OnActorClicked(AActor* TouchedActor, FKey ButtonPressed);

	UFUNCTION()
	virtual void OnActorBeginCursorOver(AActor* TouchedActor);
	
	UFUNCTION()
	virtual void OnActorEndCursorOver(AActor* TouchedActor);
	
public:
	FAxialCoordinate GetHexCoordinate() const;

	void SetHexCoordinate(const FAxialCoordinate& HexCoordinate);

	UFUNCTION(BlueprintCallable)
	bool CanAcceptNewPiece();

	bool AcceptNewPiece(AHGPieceActor* NewPiece);

	void RemovePieceReference();

	UFUNCTION()
	virtual void SetCanBeReached(bool bNewCanBeReached);
};
