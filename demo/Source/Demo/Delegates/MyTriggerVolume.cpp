// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTriggerVolume.h"

#include "Demo/DemoGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyTriggerVolume::AMyTriggerVolume()
{
 	// Set this actor to call Tick() every frame.
 	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 인스턴스를 위한 새 컴포넌트를 만들고 초기화한다.
	TriggerZone = CreateDefaultSubobject<UBoxComponent>("TrigggerZone");
	TriggerZone->SetBoxExtent(FVector(200, 200, 100));
}

void AMyTriggerVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	const auto Message = FString::Printf(TEXT("%s entered me"), *(OtherActor->GetName()));
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, Message);

	// 델리게이트를 호출한다
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		ADemoGameModeBase* MyGameMode = Cast<ADemoGameModeBase>(GameMode);
		if (MyGameMode != nullptr)
		{
			MyGameMode->MyStandardDelegate.ExecuteIfBound();

			// 파라미터를 사용해 함수 호출
			auto Color = FLinearColor(1, 0, 0, 1);
			MyGameMode->MyParameterDelegate.ExecuteIfBound(Color);

			MyGameMode->MyMulticastDelegate.Broadcast();
			
			OnPlayerEntered.Broadcast();
		}
	}
}
	
void AMyTriggerVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	const auto Message = FString::Printf(TEXT("%s left me"), *(OtherActor->GetName()));
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, Message);
}
