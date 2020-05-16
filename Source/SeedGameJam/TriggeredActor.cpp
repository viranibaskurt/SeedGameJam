// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggeredActor.h"
#include "Components/BoxComponent.h"


// Sets default values
ATriggeredActor::ATriggeredActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	TriggerBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxComp"));
	TriggerBoxComp->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBoxComp->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void ATriggeredActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggeredActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggeredActor::OnTriggeringOverlapBegin()
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));

}

void ATriggeredActor::OnTriggeringOverlapEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End"));

}

