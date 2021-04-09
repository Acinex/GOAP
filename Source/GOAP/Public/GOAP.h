// Copyright Acinex Games 2021

#pragma once

#include "CoreMinimal.h"

class FGOAPModule : public IModuleInterface
{
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;
};
