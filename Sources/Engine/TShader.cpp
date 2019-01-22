/*
	TiX Engine v2.0 Copyright (C) 2018~2019
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"
#include "TShader.h"

namespace tix
{
	TShader::TShader(const TShaderNames& InNames)
		: TResource(ERES_SHADER)
	{
		for (int32 s = 0; s < ESS_COUNT; ++s)
		{
			Names.ShaderNames[s] = InNames.ShaderNames[s];
		}
	}

	TShader::~TShader()
	{
	}

	void TShader::InitRenderThreadResource()
	{
		TI_ASSERT(ShaderResource == nullptr);
		ShaderResource = FRHI::Get()->CreateShader(Names);

		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(TShaderUpdateResource,
			FShaderPtr, Shader_RT, ShaderResource,
			{
				FRHI::Get()->UpdateHardwareResource(Shader_RT);
			});
	}

	void TShader::DestroyRenderThreadResource()
	{
		TI_ASSERT(ShaderResource != nullptr);

		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(TShaderDestroyFShader,
			FShaderPtr, Shader_RT, ShaderResource,
			{
				Shader_RT = nullptr;
			});
		ShaderResource = nullptr;
	}
}
