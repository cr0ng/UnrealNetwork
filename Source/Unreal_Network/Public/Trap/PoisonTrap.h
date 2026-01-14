// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoisonTrap.generated.h"

UCLASS()
class UNREAL_NETWORK_API APoisonTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoisonTrap();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

	void ApplyDamage();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trap")
	TObjectPtr<class USphereComponent> DamageVolume = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trap")
	TObjectPtr<class UNiagaraComponent> TrapEffect = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float DamageInterval = 0.2f;

private:
	FTimerHandle DamageTimerHandle;
	TArray<AActor*> DamageTargetActors;


};
