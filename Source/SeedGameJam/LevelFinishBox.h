// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelFinishBox.generated.h"

DECLARE_MULTICAST_DELEGATE(FLevelFinished)

UCLASS()
class SEEDGAMEJAM_API ALevelFinishBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelFinishBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	//UPROPERTY()
		FLevelFinished OnLevelFinished;

protected:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* TriggerBoxComp;

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
