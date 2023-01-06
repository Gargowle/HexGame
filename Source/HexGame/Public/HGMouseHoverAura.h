// Copyright Gargowle 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGMouseHoverAura.generated.h"

UCLASS()
class HEXGAME_API AHGMouseHoverAura : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHGMouseHoverAura();

	void SetVisibility(bool bNewVisibility);

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

};
