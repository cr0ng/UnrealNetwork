// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/PracticeDamageZone.h"
#include "Components/SphereComponent.h"

// Sets default values
APracticeDamageZone::APracticeDamageZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(20.0f);
	SetRootComponent(Collision);

	DamageZone = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	DamageZone->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void APracticeDamageZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APracticeDamageZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

