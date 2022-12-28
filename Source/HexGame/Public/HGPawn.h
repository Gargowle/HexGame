// Copyright Gargowle 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HGPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UFloatingPawnMovement;

UCLASS()
class HEXGAME_API AHGPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHGPawn();

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	USpringArmComponent* SpringArmComponent;

	UPROPERTY()
	UCameraComponent* CameraComponent;

	UPROPERTY()
	UFloatingPawnMovement* FloatingPawnMovement;

private:
	UFUNCTION()
	void ScrollRight(float Value);

	UFUNCTION()
	void ScrollFront(float Value);

	UFUNCTION()
	void ZoomUp(float Value);

	UPROPERTY()
	FRotator CameraRotator;

	UPROPERTY(EditAnywhere, meta=(Units="cm", ClampMin=1000.0f))
	float MinSpringArmLength;

	UPROPERTY(EditAnywhere, meta=(Units="cm", ClampMin=1000.0f))
	float MaxSpringArmLength;

	UPROPERTY(EditAnywhere, meta=(Units="cm/s"))
	float MaxZoomSpeed;

	float CurrentZoomSpeed;

	

};
