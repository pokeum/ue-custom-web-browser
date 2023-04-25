#include "CustomWebBrowser/Public/CustomWebBrowserModule.h"

#if PLATFORM_ANDROID
#include "Platforms/Android/CustomWebBrowserAndroidCore.h"
#elif PLATFORM_IOS
#include "Platforms/iOS/CustomWebBrowserIOSCore.h"
#endif

#define LOCTEXT_NAMESPACE "FCustomWebBrowserModule"

void FCustomWebBrowserModule::StartupModule()
{
	// This code will execute after your module is loaded into memory;
	// the exact timing is specified in the .uplugin file per-module

#if PLATFORM_ANDROID
	CustomWebBrowserCorePointer = MakeShareable(new CustomWebBrowserAndroidCore());
#elif PLATFORM_IOS
	CustomWebBrowserCorePointer = MakeShareable(new CustomWebBrowserIOSCore());
#endif
}

void FCustomWebBrowserModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.
	// For modules that support dynamic reloading, we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomWebBrowserModule, CustomWebBrowser)