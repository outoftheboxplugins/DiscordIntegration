using System.IO;
using UnrealBuildTool;

public class DiscordCppSdk : ModuleRules
{
	public DiscordCppSdk(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			string DiscordBinaries = Path.Combine(ModuleDirectory, "Binaries", "Win64");
			string PlatformBinaires = Path.Combine("$(ProjectDir)/Binaries/", Target.Platform.ToString());

			PublicDelayLoadDLLs.Add("discord_game_sdk.dll");
			PublicAdditionalLibraries.Add(Path.Combine(DiscordBinaries, "discord_game_sdk.dll.lib"));
			RuntimeDependencies.Add(Path.Combine(PlatformBinaires, "discord_game_sdk.dll"), Path.Combine(DiscordBinaries, "discord_game_sdk.dll"));
		}
	}
}
