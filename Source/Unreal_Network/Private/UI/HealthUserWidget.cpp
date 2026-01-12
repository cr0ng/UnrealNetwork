// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthUserWidget.h"

void UHealthUserWidget::PracticeSetCurrent(float CurrentHealth)
{
	Current->SetText(FText::AsNumber(FMath::RoundToInt(CurrentHealth)));
}
