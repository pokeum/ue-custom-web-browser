#pragma once

#include "CustomWebBrowserCore.h"
#include "Modules/ModuleManager.h"

typedef TSharedPtr<FCustomWebBrowserCore, ESPMode::ThreadSafe> FCustomWebBrowserCorePointer;

/**
 * Custom Web Browser Module
 */
class FCustomWebBrowser : public IModuleInterface
{
public:
	static inline FCustomWebBrowser& Get()
	{
		return FModuleManager::LoadModuleChecked<FCustomWebBrowser>("CustomWebBrowser");
	}

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	inline FCustomWebBrowserCorePointer GetCustomWebBrowser() const
	{
		return CustomWebBrowserCorePointer;
	}

protected:
	FCustomWebBrowserCorePointer CustomWebBrowserCorePointer;
};