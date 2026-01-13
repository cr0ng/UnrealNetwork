// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PracticeTCPlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;

UCLASS()
class UNREAL_NETWORK_API APracticeTCPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:
	void OnKey1Press();
	void OnKey2Press();
	void OnKey3Press();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Mapping")
	TObjectPtr<UInputMappingContext> MappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> IA_Key1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> IA_Key2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> IA_Key3 = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<class UMainHUDWidget> HUDWidget = nullptr;

	TWeakObjectPtr<class APracticeTCCharacter> ControlledCharacter = nullptr;
};
