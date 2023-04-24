#include "UtilsBlueprintFunction.h"

FString UUtilsBlueprintFunction::ReadFile(const FString& Path)
{
	// We will use this FileManager to deal with the file.
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	FString FileContent;
	// Always first check if the file that you want to manipulate exist.
	if (FileManager.FileExists(*Path))
	{
		// We use the LoadFileToString to load the file into
		if(FFileHelper::LoadFileToString(FileContent, *Path))
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Text From File:\n%s"), *FileContent);  
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Did not load text from file"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: ERROR: Can not read the file because it was not found."));
		UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Expected file location: %s"),*Path);
	}
	
	return FileContent;
}

FString UUtilsBlueprintFunction::GetSampleJavascript()
{
	// Get the path to the plugin's resources directory
	FString PluginContentDir = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("CustomWebBrowser"), TEXT("Resources"));

	// Construct the path to the file within the plugin's resources directory
	FString FilePath = FPaths::Combine(PluginContentDir, TEXT("Sample.js"));
	
	return ReadFile(FilePath);
}