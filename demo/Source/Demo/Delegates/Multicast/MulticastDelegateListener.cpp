// Fill out your copyright notice in the Description page of Project Settings.

#include "MulticastDelegateListener.h"

#include "Demo/DemoGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMulticastDelegateListener::AMulticastDelegateListener()
{
 	// Set this actor to call Tick() every frame.
 	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointLight = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	RootComponent = PointLight;
}

void AMulticastDelegateListener::ToggleLight()
{
	PointLight->ToggleVisibility();
}

// Called when the game starts or when spawned
void AMulticastDelegateListener::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		ADemoGameModeBase* MyGameMode = Cast<ADemoGameModeBase>(GameMode);
		if (MyGameMode != nullptr)
		{
			MyDelegateHandle = MyGameMode->MyMulticastDelegate.AddUObject(this, &AMulticastDelegateListener::ToggleLight);
		}
	}
}

void AMulticastDelegateListener::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		ADemoGameModeBase* MyGameMode = Cast<ADemoGameModeBase>(GameMode);
		if (MyGameMode != nullptr)
		{
			MyGameMode->MyMulticastDelegate.Remove(MyDelegateHandle);
		}
	}
}
