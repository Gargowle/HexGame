// Copyright Gargowle 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGTileActor.generated.h"

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
