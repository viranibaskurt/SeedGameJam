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
