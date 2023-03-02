// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class G20893809_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	//Spring Arm
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class USpringArmComponent* CameraSpringArm;
	//Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class UCameraComponent* CameraComponent;


	UPROPERTY()
		FVector DeltaLocation = FVector(0.0f, 0.0f, 0.0f);
	UPROPERTY()
		FQuat DeltaRotation = FQuat(0.0f, 0.0f, 0.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedModifier;

	//Movement Functions
	UFUNCTION()
		void Drive(float Value);
	UFUNCTION()
		void Strafe(float Value);
	UFUNCTION()
		void StartSprinting();
	UFUNCTION()
		void StopSprinting();

	//Gun functions
	void OnFire();


public:

	//Projectile stuff
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AProjectile> Projectile;


	//Firing sound & Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FiringSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	class UAnimInstance* AnimInstance;


	//Projectile positioning
	class UWorld* World;

	FRotator SpawnRotation;
	FVector SpawnLocation;


};
