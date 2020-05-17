// Copyright Epic Games, Inc. All Rights Reserved.

#include "SeedGameJamGameMode.h"
#include "SeedGameJamCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

#include "GamePawn.h"
#include "LevelFinishBox.h"
#include "LevelContainer.h"


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

	if (!FinishBox)
	{
		UE_LOG(LogTemp, Error, TEXT("Finish box not setted"));
		return;
	}

	if (Levels.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Levels not setted"));
	}

	FinishBox->OnLevelFinished.AddUObject(this, &ASeedGameJamGameMode::OnSuccess);

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
		Timer = 0.0f;
		OnHandEnds();
	}

	InitTimerUI(Timer); 


}

void ASeedGameJamGameMode::OnHandStarts()
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

void ASeedGameJamGameMode::OnHandEnds()
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

}

void ASeedGameJamGameMode::OnSuccess()
{
	UE_LOG(LogTemp, Error, TEXT("Success. Next level"));

	DeactivateLevel(ActiveLevelIndex);
	ActiveLevelIndex++;

	if (ActiveLevelIndex >= Levels.Num())
	{
		//GameFinishedSuccessfully
	}

	ActivateLevel(ActiveLevelIndex);

}

void ASeedGameJamGameMode::OnFail()
{

}

void ASeedGameJamGameMode::ActivateLevel(int index)
{
	if (Levels.IsValidIndex(index) && Levels[index])
	{
		Levels[index]->SetActorHiddenInGame(false);
		Levels[index]->SetActorLocation(FVector::ZeroVector);
	}
}

void ASeedGameJamGameMode::DeactivateLevel(int index)
{
	if (Levels.IsValidIndex(index) && Levels[index])
	{
		Levels[index]->SetActorHiddenInGame(true);
		Levels[index]->SetActorLocation(FVector::UpVector * 3000);
	}
}

void ASeedGameJamGameMode::Init()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(InitTimerHandle, this, &ASeedGameJamGameMode::InitDelayed, 0.1, false);
	}

	for (size_t i = 1; i < Levels.Num(); i++)
	{

		DeactivateLevel(i);
	}

}

void ASeedGameJamGameMode::InitDelayed()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearTimer(InitTimerHandle);
	}

	OnHandStarts();


}
