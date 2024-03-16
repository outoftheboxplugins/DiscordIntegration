using UnrealBuildTool;

public class DiscordIntegration : ModuleRules
{
	public DiscordIntegration(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Projects", 
			"Engine",
			"Slate",

			"DiscordCppSdk",
		});

		PrivateIncludePaths.Add("DiscordIntegration");
	}
}
