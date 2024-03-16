#pragma once

#include <Subsystems/GameInstanceSubsystem.h>

#include "DiscordSubsystem.generated.h"

namespace discord
{
	class Core;
}

/**
 * Responsible for integrating the required Discord C++ implementation and exposing it
 */
UCLASS()
class UDiscordSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void OnTick(float DeltaTime);

	void SetActivity();

	TUniquePtr<discord::Core> Core = nullptr;
};
