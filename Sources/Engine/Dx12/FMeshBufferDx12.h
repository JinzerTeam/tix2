/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

#if COMPILE_WITH_RHI_DX12

namespace tix
{
	class FMeshBufferDx12 : public FMeshBuffer
	{
	public:
		FMeshBufferDx12();
		virtual ~FMeshBufferDx12();
	protected:

	private:
		ComPtr<ID3D12Resource> VertexBuffer;
		ComPtr<ID3D12Resource> IndexBuffer;

		D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
		D3D12_INDEX_BUFFER_VIEW IndexBufferView;

		friend class FRHIDx12;
	};
}

#endif	// COMPILE_WITH_RHI_DX12