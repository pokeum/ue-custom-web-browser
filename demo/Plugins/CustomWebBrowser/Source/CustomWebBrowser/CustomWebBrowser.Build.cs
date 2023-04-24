// Some copyright should be here...

using UnrealBuildTool;

public class CustomWebBrowser : ModuleRules
{
	public CustomWebBrowser(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		// PublicDependencyModuleNames will be available in the Public and Private folders,
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Engine", "Core", "CoreUObject",
			"UMG", "Slate", "SlateCore",
			"WebBrowser",
		});
		// but PrivateDependencyModuleNames will only be available in the Private folder.
		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
