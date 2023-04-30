#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilsBlueprintFunction.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UUtilsBlueprintFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Demo")
	static FString GetSampleJavascript();
};
