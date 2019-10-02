/*
	TiX Engine v2.0 Copyright (C) 2018~2020
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
	enum E_GPU_COMMAND_TYPE
	{
		GPU_COMMAND_SET_MESH_BUFFER,
		GPU_COMMAND_DRAW_INDEXED,

		GPU_COMMAND_TYPE_COUNT
	};

	// Indirect drawing GPU command signature, contain command structure in GPU command buffer
	class FGPUCommandSignature : public FRenderResource
	{
	public:
		FGPUCommandSignature(FPipelinePtr InPipeline, const TVector<E_GPU_COMMAND_TYPE>& InCommandStructure);
		virtual ~FGPUCommandSignature();

		const TVector<E_GPU_COMMAND_TYPE>& GetCommandStructure() const
		{
			return CommandStructure;
		}

		FPipelinePtr GetPipeline()
		{
			return Pipeline;
		}

	private:

	protected:
		FPipelinePtr Pipeline;
		TVector<E_GPU_COMMAND_TYPE> CommandStructure;
	};
} // end namespace tix