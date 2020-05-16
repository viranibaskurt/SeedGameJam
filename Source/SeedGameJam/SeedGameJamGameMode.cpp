// Copyright Epic Games, Inc. All Rights Reserved.

#include "SeedGameJamGameMode.h"
#include "SeedGameJamCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

#include "GamePawn.h"


ASeedGameJamGameMode::ASeedGameJamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PrimaryActorTick.bCanEverTick = true;

}

void ASeedGameJamGameMode::BeginPlay()
{
	Super::BeginPlay();

	Init();

}

void ASeedGameJamGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (!bIsLevelRunning) return;
	
	if (Timer > 0)
	{
		Timer -= DeltaSeconds;
	}
	else
	{
		OnLevelEnds();
	}

}

void ASeedGameJamGameMode::OnLevelStarts()
{
	Timer = InitialTimer;
	bIsLevelRunning = true;

	if (ControlledPawn == NULL) return;

	ControlledPawn->StartRecording();

	ControlledPawn->SetActorLocationAndRotation(StartLocation, FRotator::ZeroRotator);


	for (size_t i = 0; i < RepeatingPawns.Num(); i++)
	{
		if (!RepeatingPawns[i]) return;

		RepeatingPawns[i]->SetActorLocationAndRotation(StartLocation, FRotator::ZeroRotator);
		RepeatingPawns[i]->SetActorHiddenInGame(true);
	}

	for (size_t i = 0; i < NumberOfRepeat; i++)
	{
		if (!RepeatingPawns[i]) return;

		RepeatingPawns[i]->StartRepeating();
		RepeatingPawns[i]->SetActorHiddenInGame(false);
	}
}

void ASeedGameJamGameMode::OnLevelEnds()
{
	bIsLevelRunning = false;

	if (ControlledPawn == NULL) return;

	ControlledPawn->StopRecording();

	for (size_t i = 0; i < NumberOfRepeat; i++)
	{
		if (!RepeatingPawns[i]) return;

		RepeatingPawns[i]->StopRepeating();
	}

	if (RepeatingPawns.IsValidIndex(NumberOfRepeat) && RepeatingPawns[NumberOfRepeat])
	{
		RepeatingPawns[NumberOfRepeat]->SetPlayerInputSet(ControlledPawn->GetPlayerInputSet());
	}

	NumberOfRepeat++;

	if (NumberOfRepeat >= RepeatingPawns.Num())
	{
		return;
	}

	OnLevelStarts();
}

void ASeedGameJamGameMode::Init()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(InitTimerHandle, this, &ASeedGameJamGameMode::InitDelayed, 0.1, false);
	}
}

void ASeedGameJamGameMode::InitDelayed()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearTimer(InitTimerHandle);
	}

	OnLevelStarts();
	

}
