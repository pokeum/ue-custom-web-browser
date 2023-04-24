// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DemoGameModeBase.generated.h"

DECLARE_DELEGATE(FStandardDelegateSignature)
DECLARE_DELEGATE_OneParam(FParamDelegateSignature, FLinearColor)

DECLARE_MULTICAST_DELEGATE(FMulticastDelegateSignature)

UCLASS()
class DEMO_API ADemoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	FStandardDelegateSignature MyStandardDelegate;
	FParamDelegateSignature MyParameterDelegate;

	FMulticastDelegateSignature MyMulticastDelegate;
};
