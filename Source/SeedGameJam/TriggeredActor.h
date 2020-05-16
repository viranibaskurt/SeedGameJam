// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggeredActor.generated.h"

UCLASS()
class SEEDGAMEJAM_API ATriggeredActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggeredActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnTriggeringOverlapBegin_BP_Event();
	
	UFUNCTION(BlueprintImplementableEvent)
		void OnTriggeringOverlapEnd_BP_Event();

	virtual void OnTriggeringOverlapBegin();
	virtual void OnTriggeringOverlapEnd();



protected:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* TriggerBoxComp;
//private:

};
