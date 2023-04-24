// Copyright © 2023 pokeum. All rights reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FCustomWebBrowserModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};