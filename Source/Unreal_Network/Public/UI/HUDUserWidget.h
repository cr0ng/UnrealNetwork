// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Character/PracticeCharacter.h"
#include "HUDUserWidget.generated.h"


/**
 * 
 */
UCLASS()
class UNREAL_NETWORK_API UHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void PracticeSetLevel(int32 InLevel);

	UFUNCTION(BlueprintCallable)
	void PracticeSetExp(float InExp);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExpText;
};
