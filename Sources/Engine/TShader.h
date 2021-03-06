/*
	TiX Engine v2.0 Copyright (C) 2018~2021
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
	struct TShaderNames
	{
		TString ShaderNames[ESS_COUNT];

		TString GetSearchKey() const
		{
			return ShaderNames[ESS_VERTEX_SHADER] +
				ShaderNames[ESS_PIXEL_SHADER] +
				ShaderNames[ESS_DOMAIN_SHADER] +
				ShaderNames[ESS_HULL_SHADER] +
				ShaderNames[ESS_GEOMETRY_SHADER];
		}
	};

	class TShader : public TResource
	{
	public:
		TShader(const TString& InComputeName);
		TShader(const TShaderNames& InNames);
		virtual ~TShader();
		
		void LoadShaderCode();
		const TStream& GetShaderCode(E_SHADER_STAGE InStage)
		{
			return ShaderCodes[InStage];
		}
		const TStream& GetComputeShaderCode()
		{
			return ShaderCodes[0];
		}

		void ReleaseShaderCode();

		virtual void InitRenderThreadResource() override;
		virtual void DestroyRenderThreadResource() override;

		FShaderPtr ShaderResource;

	protected:
		TShaderNames Names;
		TStream ShaderCodes[ESS_COUNT];
	};
}
