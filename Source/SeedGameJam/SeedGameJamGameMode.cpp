// Copyright Epic Games, Inc. All Rights Reserved.

#include "SeedGameJamGameMode.h"
#include "SeedGameJamCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASeedGameJamGameMode::ASeedGameJamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASeedGameJamGameMode::BeginPlay()
{
	Super::BeginPlay();
	OnLevelStarts();


}

void ASeedGameJamGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//if (Timer > 0)
	//{
	//	Timer -= DeltaSeconds;
	//}
	//else
	//{
	//	OnLevelEnds();
	//}

}

void ASeedGameJamGameMode::OnLevelStarts()
{
	Timer = InitialTimer;

}

void ASeedGameJamGameMode::OnLevelEnds()
{
}
