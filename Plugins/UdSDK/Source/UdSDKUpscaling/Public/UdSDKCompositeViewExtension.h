#pragma once

#include "SceneViewExtension.h"

class FUdSDKCompositeViewExtension final : public FSceneViewExtensionBase
{
public:
	FUdSDKCompositeViewExtension(const FAutoRegister& AutoRegister);

	// ISceneViewExtension interface
	void SetupViewFamily(FSceneViewFamily& InViewFamily) override {}
	void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;
	void PreRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily) override {}
		
	void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;
	void PreRenderView_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override;
	void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;
};