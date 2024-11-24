#include "Module/CustomWebBrowserBlueprint.h"

#include "Module/CustomWebBrowser.h"

FString UCustomWebBrowserBlueprint::ReadScript(const FString& Path)
{
	return FCustomWebBrowser::Get().GetCustomWebBrowser()->ReadScript(Path);
}
