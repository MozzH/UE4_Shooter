// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/GameEngine.h"
#include "Projectile.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "G20893809GameModeBase.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f); //Capsule collision

	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.4f;
	SprintSpeedModifier = 1.5f;

	//Spring Arm
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 300.0f;

	//Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(-1, .001f, FColor::Yellow, FString::Printf(TEXT("Max Speed: %f"), GetCharacterMovement()->MaxWalkSpeed));
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJumping);
	
	//Sprint
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::StopSprinting);


	//Drive & Strafe
	PlayerInputComponent->BindAxis("Drive", this, &AMyCharacter::Drive);
	PlayerInputComponent->BindAxis("Strafe", this, &AMyCharacter::Strafe);

	//Turn & LookUp
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);

}

void AMyCharacter::StartSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedModifier;
}

void AMyCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedModifier;
}



void AMyCharacter::OnFire()
{
}


void AMyCharacter::Drive(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AMyCharacter::Strafe(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}


