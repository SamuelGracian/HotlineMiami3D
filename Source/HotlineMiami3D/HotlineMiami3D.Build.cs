// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HotlineMiami3D : ModuleRules
{
	public HotlineMiami3D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"HotlineMiami3D",
			"HotlineMiami3D/Variant_Platforming",
			"HotlineMiami3D/Variant_Platforming/Animation",
			"HotlineMiami3D/Variant_Combat",
			"HotlineMiami3D/Variant_Combat/AI",
			"HotlineMiami3D/Variant_Combat/Animation",
			"HotlineMiami3D/Variant_Combat/Gameplay",
			"HotlineMiami3D/Variant_Combat/Interfaces",
			"HotlineMiami3D/Variant_Combat/UI",
			"HotlineMiami3D/Variant_SideScrolling",
			"HotlineMiami3D/Variant_SideScrolling/AI",
			"HotlineMiami3D/Variant_SideScrolling/Gameplay",
			"HotlineMiami3D/Variant_SideScrolling/Interfaces",
			"HotlineMiami3D/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
