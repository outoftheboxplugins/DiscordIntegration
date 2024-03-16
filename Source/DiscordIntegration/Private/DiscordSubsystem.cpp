#include "DiscordSubsystem.h"

#include <DiscordSDK/core.h>

DEFINE_LOG_CATEGORY_STATIC(LogDiscordSubsystem, Log, All);

void PrintDiscordLog(discord::LogLevel Level, char const* Message)
{
	const FString LogMessage = UTF8_TO_TCHAR(Message);

	switch (Level)
	{
	case discord::LogLevel::Error:
		UE_LOG(LogDiscordSubsystem, Error, TEXT("[CPP-SDK] %s"), *LogMessage);
		break;
	case discord::LogLevel::Warn:
		UE_LOG(LogDiscordSubsystem, Warning, TEXT("[CPP-SDK] %s"), *LogMessage);
		break;
	case discord::LogLevel::Info:
		UE_LOG(LogDiscordSubsystem, Display, TEXT("[CPP-SDK] %s"), *LogMessage);
		break;
	case discord::LogLevel::Debug:
		UE_LOG(LogDiscordSubsystem, Log, TEXT("[CPP-SDK] %s"), *LogMessage);
		break;
	default:
		checkNoEntry();
	}
}

void UDiscordSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	discord::Core* CoreInstance = nullptr;
	discord::Result Result = discord::Core::Create(1218468797405724743, DiscordCreateFlags_Default, &CoreInstance);
	if (Result == discord::Result::Ok)
	{
		Core = TUniquePtr<discord::Core>(CoreInstance);

		Core->SetLogHook(discord::LogLevel::Debug, PrintDiscordLog);
	}
	else
	{
		UE_LOG(LogDiscordSubsystem, Error, TEXT("Failed to initialize Core."));
	}

	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().OnPreTick().AddUObject(this, &ThisClass::OnTick);
	}

	SetActivity();
}

void UDiscordSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UDiscordSubsystem::OnTick(float DeltaTime)
{
	Core->RunCallbacks();
}

void UDiscordSubsystem::SetActivity()
{
	discord::Activity activity{};
	activity.SetDetails("Game Title");
	activity.SetState("Game Mode");
	Core->ActivityManager().UpdateActivity(
		activity,
		[](discord::Result result)
		{
			UE_LOG(LogDiscordSubsystem, Warning, TEXT("Result: %d"), result);
		}
	);
}