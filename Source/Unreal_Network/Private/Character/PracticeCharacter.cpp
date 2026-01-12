// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PracticeCharacter.h"
#include "UI/HealthUserWidget.h"
#include "UI/HUDUserWidget.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APracticeCharacter::APracticeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	HealthWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APracticeCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthWidgetComponent)
	{
		HealthUserWidget = Cast<UHealthUserWidget>(HealthWidgetComponent->GetUserWidgetObject());

		if (HealthUserWidget)
		{
			HealthUserWidget->PracticeSetCurrent(Health);
		}
	}
	if (IsLocallyControlled()) // 캐릭터 기준
	{
		HUDUserWidget = CreateWidget<UHUDUserWidget>(GetWorld(), HUDWidgetClass);
		HUDUserWidget->AddToViewport();
	}
}

// Called every frame
void APracticeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		Level++;
		Exp += 0.1f;
		Health += 1.0f;

		if (HealthUserWidget)
		{
			HealthUserWidget->PracticeSetCurrent(Health);
		}

		if (IsLocallyControlled() && HUDUserWidget)
		{
			HUDUserWidget->PracticeSetLevel(Level);
			HUDUserWidget->PracticeSetExp(Exp);
		}
	}

	const FString Str = FString::Printf(TEXT("Lv(%d), Exp(%.1f), Health(%.1f)"), Level, Exp, Health);
	DrawDebugString(GetWorld(), GetActorLocation(), Str, nullptr, FColor::Blue, 0, true);
}

// Called to bind functionality to input
void APracticeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APracticeCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APracticeCharacter, Health);
	DOREPLIFETIME_CONDITION(APracticeCharacter, Level, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(APracticeCharacter, Exp, COND_OwnerOnly);

}

void APracticeCharacter::PracticeSetLevel()
{
	if (HasAuthority())
	{
		Level++;
	}
}

void APracticeCharacter::PracticeSetHealth()
{
	if (HasAuthority())
	{
		Health += 10.0f;
	}
}

void APracticeCharacter::PracticeSetExp()
{
	if (HasAuthority())
	{
		Exp += 50.0f;
	}
}

void APracticeCharacter::OnRep_Level()
{
	if (!IsLocallyControlled()) return;
	if (IsLocallyControlled() && HUDUserWidget)
		HUDUserWidget->PracticeSetLevel(Level);
}

void APracticeCharacter::OnRep_Health()
{
	if (HealthUserWidget)
		HealthUserWidget->PracticeSetCurrent(Health);
}

void APracticeCharacter::OnRep_Exp()
{
	if (!IsLocallyControlled()) return;
	if (IsLocallyControlled() && HUDUserWidget)
		HUDUserWidget->PracticeSetLevel(Exp);
}
