// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDUserWidget.h"

void UHUDUserWidget::PracticeSetLevel(int32 InLevel)
{
	if (!LevelText) return;
	LevelText->SetText(FText::AsNumber(InLevel));
}

void UHUDUserWidget::PracticeSetExp(float InExp)
{
	if (!ExpText) return; 
	ExpText->SetText(FText::AsNumber(FMath::RoundToInt(InExp)));
}

