// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SeedGameJamGameMode.generated.h"

UCLASS(minimalapi)
class ASeedGameJamGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();

public:
	ASeedGameJamGameMode();

	virtual void Tick(float DeltaSeconds);

public:
	UPROPERTY(BlueprintReadOnly)
		TArray<class AGamePawn*> RepeatingPawns;

	UPROPERTY(EditAnywhere)
		float InitialTimer = 15.0f;

	UPROPERTY(BlueprintReadOnly)
		float Timer;
protected:
	UFUNCTION(BlueprintCallable)
		void OnLevelStarts();
	UFUNCTION(BlueprintCallable)
		void OnLevelEnds();


private:

};



