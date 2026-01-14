// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap/HealZone.h"

#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AHealZone::AHealZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	HealVolume = CreateDefaultSubobject<USphereComponent>(TEXT("HealVolume"));
	SetRootComponent(HealVolume);

	HealEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	HealEffect->SetupAttachment(RootComponent);
	HealEffect->SetAutoActivate(true);

}

// Called when the game starts or when spawned
void AHealZone::BeginPlay()
{
	Super::BeginPlay();
	
	HealVolume->OnComponentBeginOverlap.AddDynamic(this, &AHealZone::OnOverlapBegin);
	HealVolume->OnComponentEndOverlap.AddDynamic(this, &AHealZone::OnOverlapEnd);
}

void AHealZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority() && OtherActor && OtherActor != this)
	{
		HealTargetActors.AddUnique(OtherActor);

		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		if (!TimerManager.IsTimerActive(HealTimerHandle))
		{
			TimerManager.SetTimer(
				HealTimerHandle,
				this, &AHealZone::ApplyHeal,
				HealInterval, true
			);
		}
	}
}

void AHealZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HasAuthority() && OtherActor)
	{
		HealTargetActors.Remove(OtherActor);
		if (HealTargetActors.Num() <= 0)
		{
			FTimerManager& TimerManager = GetWorld()->GetTimerManager();
			TimerManager.ClearTimer(HealTimerHandle);
		}
	}
}



void AHealZone::ApplyHeal()
{
	if (HasAuthority())
	{
		for (int32 i = HealTargetActors.Num() - 1; i >= 0; --i)
		{
			AActor* Target = HealTargetActors[i];
			if (IsValid(Target))
			{
				// 피가 차도록
				UGameplayStatics::ApplyDamage(Target, -1.0f, GetInstigatorController(), this, UDamageType::StaticClass());
			}
			else
			{
				HealTargetActors.RemoveAt(i);
			}
		}
	}
}


