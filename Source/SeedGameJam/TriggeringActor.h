// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggeringActor.generated.h"

UCLASS()
class SEEDGAMEJAM_API ATriggeringActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggeringActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		class ATriggeredActor* TriggeredActor;

protected:

	UPROPERTY(VisibleAnywhere)
		USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* TriggerBoxComp;
	



	UFUNCTION(BlueprintImplementableEvent)
		void OnOverlapBegin_BP_Event();

	UFUNCTION(BlueprintImplementableEvent)
		void OnOverlapEnd_BP_Event();

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	
};
