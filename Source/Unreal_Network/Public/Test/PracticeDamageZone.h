// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "PracticeDamageZone.generated.h"

UCLASS()
class UNREAL_NETWORK_API APracticeDamageZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APracticeDamageZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	//void OnOverlap(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	//UFUNCTION(NetMulticast, Unreliable)
	//void Multicast_OverlappedDamage(const FVector& InLocation, const FRotator& InRotation);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class USphereComponent> Collision = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UNiagaraComponent> DamageZone = nullptr;

private:
	bool bOverlapped = false;
};
