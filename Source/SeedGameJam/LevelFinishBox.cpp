// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelFinishBox.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevelFinishBox::ALevelFinishBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	TriggerBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxComp"));
	TriggerBoxComp->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBoxComp->SetupAttachment(RootComp);
	TriggerBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ALevelFinishBox::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ALevelFinishBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelFinishBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelFinishBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn)
	{
		OnLevelFinished.Broadcast();
	}
}

