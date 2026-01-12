// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NetworkRoleCharacter.h"

void ANetworkRoleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	const FString LocalRoleString = UEnum::GetValueAsString(GetLocalRole());
	const FString RemoteRoleString = UEnum::GetValueAsString(GetRemoteRole());

	const FString OwnerString = GetOwner() ? GetOwner()->GetName() : TEXT("오너 없음");
	const FString ConnectionString = GetNetConnection() ? TEXT("커넥션 있음") : TEXT("커넥션 없음");
	
	const FString Values = FString::Printf(
		TEXT("LocalRole : %s\nRemoteRole : %s\nOwner : %s\nConnection : %s"), 
		*LocalRoleString, *RemoteRoleString, *OwnerString, *ConnectionString);
	DrawDebugString(GetWorld(), GetActorLocation(), Values, nullptr, FColor::Blue, 0.0f, true);
}
