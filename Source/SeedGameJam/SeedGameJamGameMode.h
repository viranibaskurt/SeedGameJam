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

	UPROPERTY(BlueprintReadWrite)
		class AGamePawn* ControlledPawn;

	UPROPERTY(BlueprintReadWrite)
		TArray<class AGamePawn*> RepeatingPawns;
	
	UPROPERTY(BlueprintReadWrite)
		FVector StartLocation;

	UPROPERTY(EditAnywhere)
		float InitialTimer = 3.0f;

	UPROPERTY(BlueprintReadOnly)
		float Timer;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<class ALevelContainer>> Levels;

	UPROPERTY(EditAnywhere)
		TSoftObjectPtr<class ALevelFinishBox> FinishBox;

	bool bIsLevelRunning;
	int NumberOfRepeat;

	int ActiveLevelIndex;

	UFUNCTION(BlueprintCallable)
		void OnHandStarts();
	UFUNCTION(BlueprintCallable)
		void OnHandEnds();
	
	UFUNCTION(BlueprintCallable)
		void OnSuccess();

	UFUNCTION(BlueprintCallable)
		void OnFail();


	UFUNCTION(BlueprintImplementableEvent)
		void InitTimerUI(float Time);

	UFUNCTION(BlueprintImplementableEvent)
		void InitNumSelfUI(int Num);

	UFUNCTION(BlueprintImplementableEvent)
		void FadeInBlack();
	UFUNCTION(BlueprintImplementableEvent)
		void FadeOutBlack();

	UFUNCTION(BlueprintImplementableEvent)
		void ShowUIState(bool State);

	void ActivateLevel(int index);
	void DeactivateLevel(int index);

private:

	UPROPERTY()
		FTimerHandle InitTimerHandle;

	UFUNCTION()
		void InitDelayed();
	void Init();

};



