// Copyright Gargowle 2022


#include "HGPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AHGPawn::AHGPawn() :
	MinSpringArmLength(1000.0f),
	MaxSpringArmLength(4000.0f),
	MaxZoomSpeed(1000.0f)
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	// No attachment necessary for movement component
	FloatingPawnMovement  = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
}

// Called to bind functionality to input
void AHGPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("ScrollRight"), this, &AHGPawn::ScrollRight);
	PlayerInputComponent->BindAxis(TEXT("ScrollFront"), this, &AHGPawn::ScrollFront);
	PlayerInputComponent->BindAxis(TEXT("ZoomUp"), this, &AHGPawn::ZoomUp);
}

void AHGPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SpringArmComponent->TargetArmLength = 0.5 * (MinSpringArmLength + MaxSpringArmLength);
	SpringArmComponent->SetRelativeRotation(FRotator(-75.0f, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;
}

void AHGPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if ((CurrentZoomSpeed < 0.0f && SpringArmComponent->TargetArmLength > MinSpringArmLength)
		|| (CurrentZoomSpeed > 0.0f && SpringArmComponent->TargetArmLength < MaxSpringArmLength)
	)
	{
		float NewLength = SpringArmComponent->TargetArmLength + DeltaSeconds * CurrentZoomSpeed;
		SpringArmComponent->TargetArmLength =
			FMath::Max(FMath::Min( NewLength, MaxSpringArmLength), MinSpringArmLength);
	}
	
}

void AHGPawn::ScrollRight(float Value)
{
	if(Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value*100);
	}
}

void AHGPawn::ScrollFront(float Value)
{
	if(Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value*100);
	}
}

void AHGPawn::ZoomUp(float Value)
{
	CurrentZoomSpeed = Value * MaxZoomSpeed;
}

