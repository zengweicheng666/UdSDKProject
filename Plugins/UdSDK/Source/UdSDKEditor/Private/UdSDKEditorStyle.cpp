// Copyright Epic Games, Inc. All Rights Reserved.

#include "UdSDKEditorStyle.h"
#include "UdSDKEditor.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Brushes/SlateImageBrush.h"
#include "Brushes/SlateBoxBrush.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr< FSlateStyleSet > FUdSDKEditorStyle::StyleInstance = NULL;

#define IMAGE_BRUSH(RelativePath, ...)                                         \
  FSlateImageBrush(                                                            \
      FUdSDKEditorStyle::Get()->RootToContentDir(RelativePath, TEXT(".png")),  \
      __VA_ARGS__)

#define BOX_BRUSH(RelativePath, ...)                                           \
  FSlateBoxBrush(                                                              \
      FUdSDKEditorStyle::Get()->RootToContentDir(RelativePath, TEXT(".png")),  \
      __VA_ARGS__)

//#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FUdSDKEditorStyle::Get()->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
//#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( FUdSDKEditorStyle::Get()->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
//#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( FUdSDKEditorStyle::Get()->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
//#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( FUdSDKEditorStyle::Get()->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
//#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( FUdSDKEditorStyle::Get()->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);
const FVector2D Icon64x64(64.0f, 64.0f);

void registerIcon(TSharedRef<FSlateStyleSet>& StyleSet, const FString& propertyName, const FString& relativePath)
{
    StyleSet->Set(FName(propertyName), new IMAGE_BRUSH(relativePath, Icon40x40));
    StyleSet->Set(FName(propertyName + ".Small"), new IMAGE_BRUSH(relativePath, Icon20x20));
}

FSlateBoxBrush createButtonBoxBrush(const FString& name, const FLinearColor& color) {
    return BOX_BRUSH(name, FMargin(4 / 16.0f), color);
}


void FUdSDKEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		//StyleInstance = Create();
        Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FUdSDKEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FUdSDKEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("UdSDKEditorStyle"));
	return StyleSetName;
}

void FUdSDKEditorStyle::Create()
{
    TSharedRef< FSlateStyleSet > StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
    StyleInstance = StyleSet;

    StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin("UdSDK")->GetBaseDir() / TEXT("Resources"));

    StyleSet->Set(
        "UdSDK.MenuIcon",
        new IMAGE_BRUSH(TEXT("UdSDK-icon-16x16"), Icon16x16));
    
    StyleSet->Set(
        "ClassIcon.udPointCloud",
        new IMAGE_BRUSH(TEXT("UdSDK-icon-16x16"), Icon16x16));
    StyleSet->Set(
        "ClassThumbnail.udPointCloud",
        new IMAGE_BRUSH(TEXT("UdSDK-64x64"), Icon64x64));

    StyleSet->Set(
        "ClassIcon.udPointOfInterest",
        new IMAGE_BRUSH(TEXT("UdSDK-icon-16x16"), Icon16x16));
    StyleSet->Set(
        "ClassThumbnail.udPointOfInterest",
        new IMAGE_BRUSH(TEXT("UdSDK-64x64"), Icon64x64));

    StyleSet->Set(
        "ClassIcon.udPolygon",
        new IMAGE_BRUSH(TEXT("UdSDK-icon-16x16"), Icon16x16));
    StyleSet->Set(
        "ClassThumbnail.udPolygon",
        new IMAGE_BRUSH(TEXT("UdSDK-64x64"), Icon64x64));
 
    registerIcon(
        StyleSet,
        "UdSDK.Common.AddFromAssets",
        "Toolbar/assets");

    registerIcon(
        StyleSet,
        "UdSDK.Common.SignOut",
        "Toolbar/sign-out");

    registerIcon(
        StyleSet,
        "UdSDK.Common.OpenSupport",
        "Toolbar/helping");
    
    registerIcon(StyleSet,
        "UdSDK.Common.OpenMainPanel", 
        "UdSDK-icon-40x40");
    
    StyleSet->Set(
        "UdSDK.Common.Refresh",
        new IMAGE_BRUSH(TEXT("Toolbar/refresh"), Icon16x16));
    
    StyleSet->Set(
        "UdSDK.Logo",
        new IMAGE_BRUSH(
            "UdSDK-Logo-01",
            FVector2D(184.0f, 150.0f)));
    
    StyleSet->Set(
        "WelcomeText",
        FTextBlockStyle()
        .SetColorAndOpacity(FSlateColor::UseForeground())
        .SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 14)));
    
    StyleSet->Set(
        "Heading",
        FTextBlockStyle()
        .SetColorAndOpacity(FSlateColor::UseForeground())
        .SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 12)));
    
    StyleSet->Set(
        "BodyBold",
        FTextBlockStyle()
        .SetColorAndOpacity(FSlateColor::UseForeground())
        .SetFont(FCoreStyle::GetDefaultFontStyle("Bold", 9)));
    
    StyleSet->Set(
        "AssetDetailsFieldHeader",
        FTextBlockStyle()
        .SetColorAndOpacity(FSlateColor::UseForeground())
        .SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 11)));
    
    StyleSet->Set(
        "AssetDetailsFieldValue",
        FTextBlockStyle()
        .SetColorAndOpacity(FSlateColor::UseForeground())
        .SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 9)));
    
    const FLinearColor UdSDKButtonLighter(0.16863f, 0.52941f, 0.76863f, 1.0f);
    const FLinearColor UdSDKButton(0.07059f, 0.35686f, 0.59216f, 1.0f);
    const FLinearColor UdSDKButtonDarker(0.05490f, 0.29412f, 0.45882f, 1.0f);
    const FButtonStyle UdSDKButtonStyle =
        FButtonStyle()
        .SetNormalPadding(FMargin(10, 5, 10, 5))
        .SetPressedPadding(FMargin(10, 5, 10, 5))
        .SetNormal(createButtonBoxBrush("UdSDKButton", UdSDKButton))
        .SetHovered(
            createButtonBoxBrush("UdSDKButton", UdSDKButtonLighter))
        .SetPressed(
            createButtonBoxBrush("UdSDKButton", UdSDKButtonDarker));
    StyleSet->Set("UdSDKButton", UdSDKButtonStyle);
    
    const FTextBlockStyle UdSDKButtonTextStyle =
        FTextBlockStyle()
        .SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f))
        .SetFont(FCoreStyle::GetDefaultFontStyle("Bold", 12));
    StyleSet->Set("UdSDKButtonText", UdSDKButtonTextStyle);
}

void FUdSDKEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

TSharedPtr< FSlateStyleSet > FUdSDKEditorStyle::Get()
{
	return StyleInstance;
}
