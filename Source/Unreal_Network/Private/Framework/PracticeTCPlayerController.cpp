// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PracticeTCPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Character/PracticeTCCharacter.h"
#include "GameFramework/PlayerState.h"
#include "UI/MainHUDWidget.h"

void APracticeTCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		if (HUDWidgetClass)
		{
			HUDWidget = CreateWidget<UMainHUDWidget>(this, HUDWidgetClass);
			if (HUDWidget.IsValid())
			{
				HUDWidget.Get()->AddToViewport();
			}
		}
	}
}

void APracticeTCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalController())
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		if (SubSystem)
		{
			SubSystem->AddMappingContext(MappingContext, 0);
		}

		UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
		if (EnhancedInput)
		{
			EnhancedInput->BindAction(IA_Key1, ETriggerEvent::Started, this, &APracticeTCPlayerController::OnKey1Press);
			EnhancedInput->BindAction(IA_Key2, ETriggerEvent::Started, this, &APracticeTCPlayerController::OnKey2Press);
			EnhancedInput->BindAction(IA_Key3, ETriggerEvent::Started, this, &APracticeTCPlayerController::OnKey3Press);
		}
	}
}

void APracticeTCPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	ControlledCharacter = Cast<APracticeTCCharacter>(aPawn);
	ControlledCharacter->OnLevelUpdated.BindWeakLambda(
		this,
		[this](int NewLevel)
		{
			if (HUDWidget.IsValid())
			{
				HUDWidget->UpdateLevel(NewLevel);
			}
		}
	);
	ControlledCharacter->OnExpUpdated.BindWeakLambda(
		this,
		[this](float NewExp)
		{
			if (HUDWidget.IsValid())
			{
				HUDWidget->UpdateExp(NewExp);
			}
		}
	);
}

void APracticeTCPlayerController::OnUnPossess()
{
	ControlledCharacter = nullptr;
	Super::OnUnPossess();
}

void APracticeTCPlayerController::OnKey1Press()
{
	const FString Str = FString::Printf(
		TEXT("%s[%d] : OnKey1Press"),
		HasAuthority() ? TEXT("Server") : TEXT("Client"),
		PlayerState->GetPlayerId());

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Str);
	if (ControlledCharacter.IsValid())
	{
		ControlledCharacter.Get()->OnKey1();
	}
}

void APracticeTCPlayerController::OnKey2Press()
{
	const FString Str = FString::Printf(
		TEXT("%s[%d] : OnKey2Press"),
		HasAuthority() ? TEXT("Server") : TEXT("Client"),
		PlayerState->GetPlayerId());

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Str);
	if (ControlledCharacter.IsValid())
	{
		ControlledCharacter.Get()->OnKey2();
	}
}

void APracticeTCPlayerController::OnKey3Press()
{
	const FString Str = FString::Printf(
		TEXT("%s[%d] : OnKey3Press"),
		HasAuthority() ? TEXT("Server") : TEXT("Client"),
		PlayerState->GetPlayerId());

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Str);
	if (ControlledCharacter.IsValid())
	{
		ControlledCharacter.Get()->OnKey3();
	}
}