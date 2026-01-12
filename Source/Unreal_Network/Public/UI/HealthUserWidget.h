// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "HealthUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_NETWORK_API UHealthUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void PracticeSetCurrent(float CurrentHealth);

protected:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Current;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Max;
};
