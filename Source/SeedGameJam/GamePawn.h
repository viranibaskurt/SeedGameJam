// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GamePawn.generated.h"


USTRUCT(BlueprintType)
struct FUserPawnInput
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		FVector MoveInput;

	UPROPERTY()
		float DeltaTime;

};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EPawnControlType :uint8
{
	RecordingUserControl,
	RepeatingUserControl,
	NotControlled
};

UCLASS()
class SEEDGAMEJAM_API AGamePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGamePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UFUNCTION(BlueprintPure)
		float GetSpeed() { return Speed; }

	UFUNCTION(BlueprintCallable)
		void SetPawnControlType(EPawnControlType CtrType) { PawnControlType = CtrType; }

	UFUNCTION(BlueprintCallable)
		void SetPlayerInputSet(TArray<FUserPawnInput> InPlayerInputs) { PlayerInputs = InPlayerInputs; }

	UFUNCTION(BlueprintPure)
		TArray<FUserPawnInput> GetPlayerInputSet() { return PlayerInputs; }

	UFUNCTION(BlueprintCallable)
		void ResetInputSet();

	UFUNCTION(BlueprintCallable)
		void StartRecording();
	UFUNCTION(BlueprintCallable)
		void StartRepeating();

	UFUNCTION(BlueprintCallable)
		void StopRecording();

	UFUNCTION(BlueprintCallable)
		void StopRepeating();


protected:
	UPROPERTY(EditDefaultsOnly)
		float InitialMoveSpeed = 180.0f;

	UPROPERTY()
		TArray< FUserPawnInput> PlayerInputs;

	EPawnControlType PawnControlType = EPawnControlType::NotControlled;

	FVector InputVector;
	float Speed;

	int RepeatedInputIndex;
	bool bIsGameRunning;

	void MoveForward(float Value);
	void MoveRight(float Value);

	FUserPawnInput CreateInput(float DeltaTime);
	void RecordInput(FUserPawnInput Input);
	void ExecuteInput(FUserPawnInput Input);

private:

};
