/*
	TiX Engine v2.0 Copyright (C) 2018~2019
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

#if COMPILE_WITH_RHI_DX12

namespace tix
{
	// Dx12 need uniform for data, resource table for textures
	class FComputeTaskDx12: public FComputeTask
	{
	public:
		FComputeTaskDx12(const TString& ComputeShaderName);
		virtual ~FComputeTaskDx12();

	protected:

	private:
		friend class FRHIDx12;
	};
}

#endif	// COMPILE_WITH_RHI_DX12