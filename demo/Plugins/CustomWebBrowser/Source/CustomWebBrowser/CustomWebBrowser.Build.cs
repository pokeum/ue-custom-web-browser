using System.IO;
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
		
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
			
			var pluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(pluginPath, "CustomWebBrowser_UPL_Android.xml"));
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			//PublicAdditionalFrameworks.Add();
			
			var pluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(pluginPath, "CustomWebBrowser_UPL_iOS.xml"));
		}
	}
}
