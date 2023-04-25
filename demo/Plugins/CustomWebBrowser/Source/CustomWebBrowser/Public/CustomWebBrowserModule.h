// Copyright © 2023 pokeum. All rights reserved.

#pragma once

#include "Interfaces/CustomWebBrowserCore.h"
#include "Modules/ModuleManager.h"

typedef TSharedPtr<ICustomWebBrowserCore, ESPMode::ThreadSafe> FCustomWebBrowserCorePointer;

class FCustomWebBrowserModule : public IModuleInterface
{
public:
	static inline FCustomWebBrowserModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FCustomWebBrowserModule>("CustomWebBrowser");
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