#pragma once

#include "ShaderParameterMacros.h"

BEGIN_SHADER_PARAMETER_STRUCT(FCompositePassParameters, )
	SHADER_PARAMETER_RDG_TEXTURE(Texture2D, InputTexture)
	SHADER_PARAMETER_RDG_TEXTURE(Texture2D, DepthTexture)
	SHADER_PARAMETER_TEXTURE(Texture2D, UdColorTexture)
	SHADER_PARAMETER_TEXTURE(Texture2D, UdDepthTexture)
END_SHADER_PARAMETER_STRUCT()