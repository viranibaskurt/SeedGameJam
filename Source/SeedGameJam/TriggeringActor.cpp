// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggeringActor.h"
#include "Components/BoxComponent.h"

#include "TriggeredActor.h"


// Sets default values
ATriggeringActor::ATriggeringActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp= CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	TriggerBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxComp"));
	TriggerBoxComp->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBoxComp->SetupAttachment(RootComp);
	TriggerBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ATriggeringActor::OnOverlapBegin);
	TriggerBoxComp->OnComponentEndOverlap.AddDynamic(this, &ATriggeringActor::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ATriggeringActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggeringActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggeringActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!TriggeredActor) return;

	APawn* Pawn = Cast<APawn>(OtherActor);

	if (Pawn)
	{
		OnOverlapBegin_BP_Event();
		TriggeredActor->OnTriggeringOverlapBegin();
	}

}

void ATriggeringActor::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

	if (!TriggeredActor) return;

	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn)
	{
		OnOverlapEnd_BP_Event();
		TriggeredActor->OnTriggeringOverlapEnd();
	}
}

