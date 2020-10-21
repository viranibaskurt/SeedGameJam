// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePawn.h"

#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AGamePawn::AGamePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	//CapsuleComp->SetupAttachment(RootComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(CapsuleComp);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);

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
		Speed = 0;
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

void AGamePawn::SetRagdollState(bool State)
{
	SetRagdollState_BP(State);
}

void AGamePawn::Explode()
{
	SetPawnControlType(EPawnControlType::NotControlled);
	//Explode_BP();
	if (CapsuleComp)
	{
		CapsuleComp->SetEnableGravity(true);
	}
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

void AGamePawn::ResetForces()
{
	if (CapsuleComp)
	{
		CapsuleComp->SetEnableGravity(false);
		CapsuleComp->SetSimulatePhysics(false);
		CapsuleComp->SetSimulatePhysics(true);
	}

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
}

void AGamePawn::ExecuteInput(FUserPawnInput Input)
{
	AddActorWorldOffset(Input.MoveInput.GetSafeNormal() * Input.DeltaTime * InitialMoveSpeed, true);

	if (Input.MoveInput.SizeSquared() > 0)
	{
		FRotator Rot = UKismetMathLibrary::MakeRotFromX(Input.MoveInput.RotateAngleAxis(-90, FVector(0, 0, 1)));
		SetActorRotation(Rot);
	}

	Speed = Input.MoveInput.Size() * 375;

}



