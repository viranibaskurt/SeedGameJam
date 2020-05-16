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


	if (PawnControlType == EPawnControlType::RecordingUserControl)
	{
		FUserPawnInput CurrentInput = CreateInput(DeltaTime);
		RecordInput(CurrentInput);
		ExecuteInput(CurrentInput);
	}
	else if (PawnControlType == EPawnControlType::RepeatingUserControl)
	{
		if (PlayerInputs.IsValidIndex(RepeatedInputIndex))
		{
			ExecuteInput(PlayerInputs[RepeatedInputIndex]);
			RepeatedInputIndex++;

		}
	}
	else if (PawnControlType == EPawnControlType::NotControlled)
	{
		ExecuteInput(CreateInput(0));
		InputVector = FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void AGamePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGamePawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGamePawn::MoveRight);
}


void AGamePawn::ResetInputSet()
{
	PlayerInputs.Empty();
}

void AGamePawn::StartRecording()
{
	ResetInputSet();
	SetPawnControlType(EPawnControlType::RecordingUserControl);
}

void AGamePawn::StartRepeating()
{
	RepeatedInputIndex = 0;
	SetPawnControlType(EPawnControlType::RepeatingUserControl);
}

void AGamePawn::StopRecording()
{
	SetPawnControlType(EPawnControlType::NotControlled);
}

void AGamePawn::StopRepeating()
{
	SetPawnControlType(EPawnControlType::NotControlled);
}


void AGamePawn::MoveForward(float Value)
{
	InputVector.X = Value;
}

void AGamePawn::MoveRight(float Value)
{
	InputVector.Y = Value;
}

FUserPawnInput AGamePawn::CreateInput(float DeltaTime)
{
	FUserPawnInput TempInput;
	TempInput.MoveInput = InputVector;
	TempInput.DeltaTime = DeltaTime;
	return TempInput;
}

void AGamePawn::RecordInput(FUserPawnInput Input)
{
	PlayerInputs.Add(Input);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), PlayerInputs.Num());
}

void AGamePawn::ExecuteInput(FUserPawnInput Input)
{
	//if (PawnControlType == EPawnControlType::RepeatingUserControl)
	//{
	//	FString debug = Input.MoveInput.ToString();
	//	UE_LOG(LogTemp, Warning, TEXT("%f"), Input.DeltaTime);
	//}
	AddActorWorldOffset(Input.MoveInput.GetSafeNormal() * Input.DeltaTime * InitialMoveSpeed, false);

	FRotator Rot = UKismetMathLibrary::MakeRotFromX(Input.MoveInput.RotateAngleAxis(-90, FVector(0, 0, 1)));
	SetActorRotation(Rot);

	Speed = Input.MoveInput.Size() * 375;

}



