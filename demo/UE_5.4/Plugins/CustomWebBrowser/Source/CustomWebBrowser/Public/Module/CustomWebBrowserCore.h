#pragma once

class CUSTOMWEBBROWSER_API FCustomWebBrowserCore
{
public:
	FString ReadScript(const FString& Path) const;

private:
	FString ReadFile(const FString& Path) const;
};