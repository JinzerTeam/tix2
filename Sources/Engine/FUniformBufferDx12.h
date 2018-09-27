/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

#if COMPILE_WITH_RHI_DX12

namespace tix
{
	class FUniformBufferDx12 : public FUniformBuffer
	{
	public:
		FUniformBufferDx12(uint32 UBFlag);
		virtual ~FUniformBufferDx12();

		virtual void Destroy() override;
	protected:

	private:
		ComPtr<ID3D12Resource> ConstantBuffer;
		uint32 CbvDescriptor;
		friend class FRHIDx12;
	};
}

#endif	// COMPILE_WITH_RHI_DX12
