// Copyright Acinex Games 2021

#include "GOAP.h"

#include "GOAPSettings.h"
#include "ISettingsModule.h"

#define LOCTEXT_NAMESPACE "FGOAPModule"

void FGOAPModule::StartupModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Goal Orientated Action Planning",
		                                 LOCTEXT("RuntimeSettingsName", "GOAP Settings"),
		                                 LOCTEXT("RuntimeSettingsDescription", "Configure the Settings for the GOAP Plugin"),
		                                 GetMutableDefault<UGOAPSettings>()
		);
	}
}

void FGOAPModule::ShutdownModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		SettingsModule->UnregisterSettings("Project", "Plugins", "Goal Orientated Action Planning");
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGOAPModule, GOAP)
