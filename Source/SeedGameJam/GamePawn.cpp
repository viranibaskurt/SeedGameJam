// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePawn.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGamePawn::AGamePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGamePawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGamePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	Speed = InputVector.Size() * 375;
	if (InputVector.SizeSquared() > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("input vector : %s"), *InputVector.ToString());


		AddActorWorldOffset(InputVector.GetSafeNormal() * GetWorld()->GetDeltaSeconds() * InitialMoveSpeed, false);

		FRotator Rot = UKismetMathLibrary::MakeRotFromX(InputVector.RotateAngleAxis(-90, FVector(0, 0, 1)));
		SetActorRotation(Rot);
	}

}

// Called to bind functionality to input
void AGamePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveForward", this, &AGamePawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGamePawn::MoveRight);
}

void AGamePawn::MoveForward(float Value)
{
	//if (Value != 0.0f)
	{
		//const FRotator Rotation = GetActorRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);

		//const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) /** Value*/;
		//UE_LOG(LogTemp, Warning, TEXT("move forward : %s"), *Direction.ToString());
		////AddMovementInput(Direction, Value);
		////AddActorWorldOffset(Direction.GetSafeNormal() * GetWorld()->GetDeltaSeconds()*150, false);
		//AddMovementInput(Direction, Value);
		////AddActorWorldOffset(FVector::RightVector * 10, false);
		InputVector.X = Value;

	}


}

void AGamePawn::MoveRight(float Value)
{
	//if (Value != 0.0f)
	{
		//const FRotator Rotation = GetActorRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);

		//const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) /** (-Value)*/;
		////AddMovementInput(Direction, Value);
		//UE_LOG(LogTemp, Warning, TEXT("move right : %s"), *Direction.ToString());

		////AddActorWorldOffset(Direction.GetSafeNormal() * GetWorld()->GetDeltaSeconds()  * 150, false);
		//AddMovementInput(Direction, Value);
		InputVector.Y = Value;
	}

}

