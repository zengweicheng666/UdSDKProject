#include "UdsSubpassComposite.h"
#include "UdSDKComposite.h"
#include "Engine/TextureRenderTarget2D.h"

static int32 GUdsComposite = 1;
static FAutoConsoleVariableRef CVarUdsComposite(
	TEXT("r.Uds.Composite.Enabled"),
	GUdsComposite,
	TEXT("Uds Composite Enabled = 1 or 0"),
	ECVF_RenderThreadSafe);



///
/// PIXEL SHADER
///
class FUdsCompositePS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FUdsCompositePS);
	SHADER_USE_PARAMETER_STRUCT(FUdsCompositePS, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_STRUCT_INCLUDE(FCompositePassParameters, Composite)
		RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
	}
};

IMPLEMENT_GLOBAL_SHADER(FUdsCompositePS, "/Plugins/UdSDK/Private/Uds_Composite.usf", "MainPS", SF_Pixel);

void FUdsSubpassComposite::ParseEnvironment(FRDGBuilder& GraphBuilder, const FViewInfo& View, const FInputs& PassInputs)
{
	Data->bEnabled = GUdsComposite > 0;// && Data->UdColorTexture&& Data->UdDepthTexture;
}

void FUdsSubpassComposite::CreateResources(FRDGBuilder& GraphBuilder, const FViewInfo& View, const FInputs& PassInputs)
{
	if (Data->bEnabled)
	{
		const FSceneRenderTargets& SceneContext = FSceneRenderTargets::Get(GraphBuilder.RHICmdList);
		Data->SceneDepthTexture = GraphBuilder.RegisterExternalTexture(SceneContext.SceneDepthZ, TEXT("SceneDepthTexture"));
		//Data->SceneDepthTexture = GraphBuilder.RegisterExternalTexture(SceneContext.EditorPrimitivesDepth, ERenderTargetTexture::Targetable);
		//Data->SceneDepthTexture = GraphBuilder.RegisterExternalTexture(SceneContext.EditorPrimitivesDepth);
		Data->CurrentInputTexture = PassInputs.SceneColor.Texture;

		Data->OutputViewport = FScreenPassTextureViewport(PassInputs.SceneColor);
		Data->InputViewport = FScreenPassTextureViewport(PassInputs.SceneColor);
	}
}

void FUdsSubpassComposite::PostProcess(FRDGBuilder& GraphBuilder, const FViewInfo& View, const FInputs& PassInputs)
{
	if (Data->bEnabled)
	{
		FScreenPassRenderTarget Output = PassInputs.OverrideOutput;

		FUdsCompositePS::FParameters* PassParameters = GraphBuilder.AllocParameters<FUdsCompositePS::FParameters>();

		PassParameters->Composite.InputTexture = Data->CurrentInputTexture;
		PassParameters->Composite.DepthTexture = Data->SceneDepthTexture;
		PassParameters->Composite.UdColorTexture = Data->UdColorTexture->GetTexture2D();
		PassParameters->Composite.UdDepthTexture = Data->UdDepthTexture->GetTexture2D();

		PassParameters->RenderTargets[0] = FRenderTargetBinding(Output.Texture, ERenderTargetLoadAction::ENoAction);

		TShaderMapRef<FUdsCompositePS> PixelShader(View.ShaderMap);

		AddDrawScreenPass(GraphBuilder,
			RDG_EVENT_NAME("UdsSubpassComposite (PS)"),
			View, Data->OutputViewport, Data->InputViewport,
			PixelShader, PassParameters,
			EScreenPassDrawFlags::None
		);

		Data->FinalOutput = Output;
		Data->CurrentInputTexture = Output.Texture;
	}
}