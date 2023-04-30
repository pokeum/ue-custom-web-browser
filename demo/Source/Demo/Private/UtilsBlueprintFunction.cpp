#include "UtilsBlueprintFunction.h"

#include "CustomWebBrowser.h"

FString UUtilsBlueprintFunction::GetSampleJavascript()
{
	return FCustomWebBrowser::Get().GetCustomWebBrowser()->ReadScript(TEXT("Sample.js"));
}