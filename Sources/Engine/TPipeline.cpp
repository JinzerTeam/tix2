/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"
#include "TPipeline.h"

namespace tix
{
	TPipeline::TPipeline()
		: TResource(ERES_PIPELINE)
	{
	}

	TPipeline::~TPipeline()
	{
	}

	void TPipeline::SetShader(E_SHADER_STAGE ShaderStage, const TString& ShaderName, const int8* InShaderCode, int32 CodeLength)
	{
		Desc.ShaderName[ShaderStage] = ShaderName;
		ShaderCode[ShaderStage].Put(InShaderCode, CodeLength);
	}
	
	void TPipeline::InitRenderThreadResource()
	{
		TI_ASSERT(PipelineResource == nullptr);
		PipelineResource = FRHI::Get()->CreatePipeline();

		ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(TPipelineUpdateResource,
			FPipelinePtr, Pipeline_RT, PipelineResource,
			TPipelinePtr, PipeDesc, this,
			{
				RHI->UpdateHardwareBuffer(Pipeline_RT, PipeDesc);
			});
	}

	void TPipeline::DestroyRenderThreadResource()
	{
		TI_ASSERT(PipelineResource != nullptr);

		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(TPipelineDestroyFPipeline,
			FPipelinePtr, Pipeline_RT, PipelineResource,
			{
				Pipeline_RT->Destroy();
			});
		PipelineResource = nullptr;
	}

	TPipelinePtr TPipeline::CreatePipeline(const TString& VsPath, const TString& PsPath, const uint32 VsFormat)
	{
		TPipelinePtr Pipeline = ti_new TPipeline;

		TString VsName, PsName;
		size_t VsStart = VsPath.rfind('/');
		if (VsStart == TString::npos)
			VsStart = -1;
		VsName = VsPath.substr(VsStart + 1);
		size_t PsStart = PsPath.rfind('/');
		if (PsStart == TString::npos)
			PsStart = -1;
		PsName = PsPath.substr(PsStart + 1);

		// Load shader code
		TFile fvs, fps;
		if (fvs.Open(VsPath, EFA_READ))
		{
			Pipeline->Desc.ShaderName[ESS_VERTEX_SHADER] = VsName;
			Pipeline->ShaderCode[ESS_VERTEX_SHADER].Put(fvs);
			fvs.Close();
		}
		if (fps.Open(PsPath, EFA_READ))
		{
			Pipeline->Desc.ShaderName[ESS_PIXEL_SHADER] = PsName;
			Pipeline->ShaderCode[ESS_PIXEL_SHADER].Put(fps);
		}
		Pipeline->Desc.VsFormat = VsFormat;
		Pipeline->InitRenderThreadResource();

		return Pipeline;
	}
}
