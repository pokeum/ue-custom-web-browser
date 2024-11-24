#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomWebBrowserBlueprint.generated.h"

UCLASS()
class CUSTOMWEBBROWSER_API UCustomWebBrowserBlueprint : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Custom Web Browser")
	static FString ReadScript(const FString& Path);
};
