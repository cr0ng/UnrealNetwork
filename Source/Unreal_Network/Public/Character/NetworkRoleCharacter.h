// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ConnectionCharacter.h"
#include "NetworkRoleCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_NETWORK_API ANetworkRoleCharacter : public ACharacter
{
	GENERATED_BODY()
	
protected:
	virtual void Tick(float DeltaTime) override;
};
