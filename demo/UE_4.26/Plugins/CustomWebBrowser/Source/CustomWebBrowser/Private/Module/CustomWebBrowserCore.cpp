#include "Module/CustomWebBrowserCore.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include <android/log.h>
#elif PLATFORM_IOS
#else
#endif

FString FCustomWebBrowserCore::ReadScript(const FString& Path) const
{
	FString Script = TEXT("");	// Empty String
	
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Method = FJavaWrapper::FindMethod(Env,
			FJavaWrapper::GameActivityClassID,
			"cwbGetAssets", "(Ljava/lang/String;)Ljava/lang/String;", false);
		jstring JFilePath = Env->NewStringUTF(TCHAR_TO_UTF8(*Path));
		jstring JFileContent = (jstring) FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method, JFilePath);

		if (JFileContent != nullptr) { Script = FJavaHelper::FStringFromParam(Env, JFileContent); }
	}
#elif PLATFORM_IOS
#else
	const FString FilePath = FPaths::Combine(FPaths::ProjectPluginsDir(),
		TEXT("CustomWebBrowser"), TEXT("Resources"), TEXT("Scripts"), Path);
	Script = ReadFile(FilePath);
#endif
	
	return Script;
}

/**
 * File manipulation: Read
 * https://unrealcommunity.wiki/revisions/6100e80f9c9d1a89e0c30e12
 */
FString FCustomWebBrowserCore::ReadFile(const FString& Path) const
{
	// We will use this FileManager to deal with the file.
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	FString FileContent;
	
	// Always first check if the file that you want to manipulate exist.
	if (FileManager.FileExists(*Path))
	{
		// We use the LoadFileToString to load the file into FileContent.
		if (! FFileHelper::LoadFileToString(FileContent, *Path))
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Did not load text from file"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: ERROR: Can not read the file because it was not found."));
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Expected file location: %s"), *Path);
	}
	
	return FileContent;
}
