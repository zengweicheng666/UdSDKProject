// Copyright Epic Games, Inc. All Rights Reserved.

#include "UdSDKUpscaling.h"
#include "Interfaces/IPluginManager.h"
#include "UdSDKComposite.h"

#define LOCTEXT_NAMESPACE "FUdSDKUpscalingModule"

void FUdSDKUpscalingModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("UdSDK"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/Plugins/UdSDK"), PluginShaderDir);

	if (CUdSDKComposite::Get() == nullptr)
		new CUdSDKComposite();
}

void FUdSDKUpscalingModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (CUdSDKComposite::Get())
		delete CUdSDKComposite::Get();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUdSDKUpscalingModule, UdSDKUpscaling)