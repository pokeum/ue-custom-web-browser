using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class CustomWebBrowser : ModuleRules
	{
		public CustomWebBrowser(ReadOnlyTargetRules Target) : base(Target)
		{
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"WebBrowser",
					"Slate",
					"SlateCore",
					"UMG",
					"Engine"
				}
			);

			if (Target.bBuildEditor == true)
			{
				//@TODO: UnrealEd Needed for the triangulation code used for sprites (but only in editor mode)
				//@TOOD: Try to move the code dependent on the triangulation code to the editor-only module
				PrivateIncludePathModuleNames.AddRange(
					new string[]
					{
						"UnrealEd",
					}
				);
				PrivateDependencyModuleNames.AddRange(
					new string[]
					{
						"EditorFramework",
						"UnrealEd",
					}
				);
			}

			if (Target.bBuildEditor || Target.Platform == UnrealTargetPlatform.Android ||
			    Target.Platform == UnrealTargetPlatform.IOS)
			{
				// WebBrowserTexture required for cooking Android
				PrivateIncludePathModuleNames.AddRange(
					new string[]
					{
						"WebBrowserTexture",
					}
				);
				PrivateDependencyModuleNames.AddRange(
					new string[]
					{
						"WebBrowserTexture",
					}
				);

				if (Target.Platform == UnrealTargetPlatform.Android)
				{
					PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
					
					string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
					AdditionalPropertiesForReceipt.Add("AndroidPlugin",
						Path.Combine(PluginPath, "CustomWebBrowser_UPL_Android.xml"));
				}
				else if (Target.Platform == UnrealTargetPlatform.IOS)
				{
					var pluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
					AdditionalPropertiesForReceipt.Add("IOSPlugin",
						Path.Combine(pluginPath, "CustomWebBrowser_UPL_iOS.xml"));
				}
			}
		}
	}
}