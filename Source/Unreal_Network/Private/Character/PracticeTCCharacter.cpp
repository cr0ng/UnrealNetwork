// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PracticeTCCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Components/WidgetComponent.h"
#include "UI/DataLineWidget.h"
#include "Framework/PracticeTCPlayerController.h"

// Sets default values
APracticeTCCharacter::APracticeTCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HealthWidgetComponent->SetupAttachment(RootComponent);
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
}

// Called when the game starts or when spawned
void APracticeTCCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (HealthWidgetComponent && HealthWidgetComponent->GetWidget())
	{
		HealthWidget = Cast<UDataLineWidget>(HealthWidgetComponent->GetWidget());
		HealthWidget->UpdateName(FText::FromString(TEXT("Health")));

	}
}

// Called every frame
void APracticeTCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 카메라에 항상 위젯이 보이도록 (지피티용)
	/*APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	FVector WorldPos = GetActorLocation() + FVector(0, 0, 100.0f);

	FVector2D ScreenPos;
	if (!PC->ProjectWorldLocationToScreen(WorldPos, ScreenPos))
		return;

	FVector CameraLocation;
	FVector CameraDirection;
	PC->DeprojectScreenPositionToWorld
	(
		ScreenPos.X,
		ScreenPos.Y,
		CameraLocation,
		CameraDirection
	);

	float FixedDistance = 200.0f;
	FVector WidgetWorldPos = CameraLocation + CameraDirection * FixedDistance;

	HealthWidgetComponent->SetWorldLocation(WidgetWorldPos);

	FRotator LookAtRot =
		(CameraLocation - WidgetWorldPos).Rotation();
	HealthWidgetComponent->SetWorldRotation(LookAtRot);*/

	// 카메라에 항상 위젯 보이도록(선생님)
	if (HealthWidgetComponent)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC && PC->PlayerCameraManager)
		{
			// 회전 -> 벡터 만들기 가능 ( 해당 회전으로 인한 Forward 벡터를 만듦)
			// 벡터 -> 회전 만들기 가능

			FVector CameraForward = PC->PlayerCameraManager->GetCameraRotation().Vector(); // 카메라의 Forward 벡터
			FVector WidgetForward = CameraForward * -1.0f;

			HealthWidgetComponent->SetWorldRotation(WidgetForward.Rotation());
			
		}
	}
}

// Called to bind functionality to input
void APracticeTCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APracticeTCCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APracticeTCCharacter, Health);
	DOREPLIFETIME_CONDITION(APracticeTCCharacter, Level, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(APracticeTCCharacter, Exp, COND_OwnerOnly);
}

void APracticeTCCharacter::OnRef_Level()
{
	UpdateLevel();
}

void APracticeTCCharacter::OnRef_Exp()
{
	UpdateExp();
}

void APracticeTCCharacter::OnRef_Health()
{
	UpdateHealth();	// 클라이언트는 리플리케이션을 받아서 업데이트
}

void APracticeTCCharacter::UpdateLevel()
{
	OnLevelUpdated.Execute(Level);
}

void APracticeTCCharacter::UpdateExp()
{
	OnExpUpdated.Execute(Exp);
}

void APracticeTCCharacter::UpdateHealth()
{
	if (HealthWidget.IsValid())
	{
		HealthWidget->UpdateFloatValue(Health);
	}
}

void APracticeTCCharacter::OnKey1()
{
	if (HasAuthority())
	{
		Level++;
		UpdateLevel();
	}
}

void APracticeTCCharacter::OnKey2()
{
	if (HasAuthority())
	{
		Exp += 1.0f;
		UpdateExp();
	}
}

void APracticeTCCharacter::OnKey3()
{
	if (HasAuthority())
	{
		Health -= 10.0f;
		UpdateHealth();	// 서버는 직접 업데이트
	}
}

