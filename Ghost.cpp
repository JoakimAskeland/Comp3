// Fill out your copyright notice in the Description page of Project Settings.



#include "Ghost.h"
#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraActor.h"
#include "Bullet.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine/Engine.h"

// Sets default values
AGhost::AGhost()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GhostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GhostMesh"));
	SetRootComponent(GhostMesh);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CurrentVelocity = FVector(0.f);
	MaxSpeed = 100.f;


	//SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);

	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;

	SpringArm->SetupAttachment(GhostMesh);


	//Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void AGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AGhost::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AGhost::MoveRight);

}

void AGhost::MoveForward(float value)
{
	CurrentVelocity.X = FMath::Clamp(value, -5.f, 5.f) * MaxSpeed;  //Moves Ghost forward or backwards. 5 is the speed of movement, if it is to be changed it needs to be done both here and in Unreal (Engine, Input)
}

void AGhost::MoveRight(float value)
{
	CurrentVelocity.Y = FMath::Clamp(value, -5.f, 5.f) * MaxSpeed;  //Moves Ghost left or right. 5 is the speed of movement, if it is to be changed it needs to be done both here and in Unreal (Engine, Input)
}

void AGhost::Shoot()
{
	if (Ammo > 5)
	{
		Ammo--;

		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::Printf(TEXT("Ammo : %d "), Ammo));

		UWorld* World = GetWorld();
		if (World)
		{
			FVector Location = GetActorLocation();
			GetWorld()->SpawnActor<ABullet>(Location + FVector(50.f, 0.f, 0.f), GetActorRotation());
		}
	}
}

void AGhost::Reload()
{
	if (Ammo < 10)
	{
		Ammo = 10;
		UWorld* NewWorld = GetWorld();
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, FString::Printf(TEXT("Reloaded")));
	}
}