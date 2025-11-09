// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BoyAdventurePatrones : ModuleRules
{
	public BoyAdventurePatrones(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
