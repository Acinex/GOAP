// Acinex Games 2021

using UnrealBuildTool;

public class GOAP : ModuleRules
{
	public GOAP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[] {"Core"});

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"AIModule"
			}
		);
	}
}