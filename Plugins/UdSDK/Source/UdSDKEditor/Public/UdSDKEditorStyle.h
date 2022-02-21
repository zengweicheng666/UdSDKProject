// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FUdSDKEditorStyle
{
public:

	static void Initialize();

	static void Shutdown();

	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	/** @return The Slate style set for the Shooter game */
	static TSharedPtr< class FSlateStyleSet > Get();

	static FName GetStyleSetName();

private:

	static void Create();

private:

	static TSharedPtr< class FSlateStyleSet > StyleInstance;
};