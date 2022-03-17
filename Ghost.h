// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Ghost.generated.h"

UCLASS()
class COMP3_API AGhost : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GhostMesh")
		UStaticMeshComponent* GhostMesh = nullptr; //endre til SkeletalMesh?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GhostMesh")
		USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GhostMesh")
		UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, Category = "Pawn Movement")
		float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GhostMesh")
		int Ammo = 10;

private:

	void MoveForward(float value);
	void MoveRight(float value);

	void Shoot();
	void Reload();

	FVector CurrentVelocity;

};
