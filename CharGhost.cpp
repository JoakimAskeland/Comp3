// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraActor.h"
#include "Bullet.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine/Engine.h"
#include "CharGhost.h"

// Sets default values
ACharGhost::ACharGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharGhostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharGhostMesh"));
	SetRootComponent(CharGhostMesh);

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

	SpringArm->SetupAttachment(CharGhostMesh);


	//Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void ACharGhost::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACharGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACharGhost::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACharGhost::MoveRight);
}


void ACharGhost::MoveForward(float value)
{
	//CurrentVelocity.X = FMath::Clamp(value, -5.f, 5.f) * MaxSpeed;  //Moves CharGhost forward or backwards. 5 is the speed of movement, if it is to be changed it needs to be done both here and in Unreal (Engine, Input)

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);

}

void ACharGhost::MoveRight(float value)
{
	//CurrentVelocity.Y = FMath::Clamp(value, -5.f, 5.f) * MaxSpeed;  //Moves CharGhost left or right. 5 is the speed of movement, if it is to be changed it needs to be done both here and in Unreal (Engine, Input)

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);

}

