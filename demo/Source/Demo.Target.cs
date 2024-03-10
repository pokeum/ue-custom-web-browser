// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DemoTarget : TargetRules
{
	public DemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "Demo" } );
		
		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			bOverrideBuildEnvironment = true;
			AdditionalCompilerArguments =
				" -Wno-bitwise-instead-of-logical" +
				" -Wno-unused-but-set-variable" +
				" -Wno-deprecated-builtins" +
				" -Wno-bitfield-constant-conversion" +
				" -Wno-unknown-warning-option";
		}
	}
}
