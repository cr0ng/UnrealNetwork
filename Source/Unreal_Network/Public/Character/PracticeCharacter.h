// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PracticeCharacter.generated.h"

class UWidgetComponent;
class UHUDUserWidget;

UCLASS()
class UNREAL_NETWORK_API APracticeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APracticeCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UFUNCTION(BlueprintCallable)
	void PracticeSetLevel();

	UFUNCTION(BlueprintCallable)
	void PracticeSetHealth();

	UFUNCTION(BlueprintCallable)
	void PracticeSetExp();

	UFUNCTION()
	void OnRep_Level();
	UFUNCTION()
	void OnRep_Health();
	UFUNCTION()
	void OnRep_Exp();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_Level, BlueprintReadOnly)
	int32 Level = 1;

	UPROPERTY(ReplicatedUsing = OnRep_Health)
	float Health = 100.0f;

	UPROPERTY(ReplicatedUsing = OnRep_Exp, BlueprintReadOnly)
	float Exp = 0.0f;


	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UWidgetComponent> HealthWidgetComponent = nullptr;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "UI")
	UWidgetComponent* HealthWidgetComponent = nullptr;

	UPROPERTY()
	class UHealthUserWidget* HealthUserWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* HUDWidgetComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UHUDUserWidget> HUDWidgetClass;

	UPROPERTY()
	UHUDUserWidget* HUDUserWidget; 
};
