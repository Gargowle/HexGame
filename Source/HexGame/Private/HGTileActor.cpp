// Copyright Gargowle 2022


#include "HGTileActor.h"

#include "HGGameModeBase.h"

#define Z_POSITION_OFFSET_LIMIT 20.0f

// Sets default values
AHGTileActor::AHGTileActor()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HexMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(TEXT("UI"));
	
	// assume default values
	HexCoord = FAxialCoordinate();
}

// Called when the game starts or when spawned
void AHGTileActor::BeginPlay()
{
	Super::BeginPlay();
}

void AHGTileActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnClicked.AddUniqueDynamic(this, &AHGTileActor::OnActorClicked);
	OnBeginCursorOver.AddUniqueDynamic(this, &AHGTileActor::OnActorBeginCursorOver);
	OnEndCursorOver.AddUniqueDynamic(this, &AHGTileActor::OnActorEndCursorOver);
}

float AHGTileActor::GetRandomZOffset()
{
	return FMath::RandRange(- Z_POSITION_OFFSET_LIMIT, Z_POSITION_OFFSET_LIMIT);
}

FAxialCoordinate AHGTileActor::GetHexCoordinate() const
{
	return HexCoord;
}

void AHGTileActor::SetHexCoordinate(const FAxialCoordinate& HexCoordinate)
{
	HexCoord = HexCoordinate;
	SetActorLocation(HexCoordinate.ToWorldCoordinate() + FVector(0,0, GetRandomZOffset()));
}

void AHGTileActor::OnActorClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	AHGGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AHGGameModeBase>();
	if(ensure(GameMode))
	{
		AHGPieceActor* ActivePiece = GameMode->ActivePiece;
		ActivePiece->MovePiece(this->HexCoord);		
	}
}

void AHGTileActor::OnActorBeginCursorOver(AActor* TouchedActor)
{
	AHGGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AHGGameModeBase>();
	if(ensure(GameMode))
	{
		AHGMouseHoverAura* Aura = Cast<AHGMouseHoverAura>(GameMode->MouseHoverAuraActor);
		
		// only do something if the aura is not already owned by this tile
		if(ensure(Aura) && Aura->GetOwner() != this)
		{
			Aura->SetOwner(this);
			Aura->TeleportTo(GetActorLocation(), GetActorRotation(), false, true);
			Aura->SetVisibility(true);
		}
	}
}

void AHGTileActor::OnActorEndCursorOver(AActor* TouchedActor)
{
	AHGGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AHGGameModeBase>();
	if(ensure(GameMode))
	{
		AHGMouseHoverAura* Aura = GameMode->MouseHoverAuraActor;

		// only do something if the aura is still owned by this tile
		if(ensure(Aura) && Aura->GetOwner() == this)
		{
			Aura->SetOwner(GameMode);
			Aura->SetVisibility(false);
		}
	}
}

