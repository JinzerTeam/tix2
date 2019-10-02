/*
	TiX Engine v2.0 Copyright (C) 2018~2020
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"
#include "FRHIDx12.h"
#include "FGPUCommandSignatureDx12.h"
#include "FGPUCommandBufferDx12.h"
#include "FMeshBufferDx12.h"

#if COMPILE_WITH_RHI_DX12
namespace tix
{
	FGPUCommandBufferDx12::FGPUCommandBufferDx12(FGPUCommandSignaturePtr Signature, uint32 InCommandsCount)
		: FGPUCommandBuffer(Signature, InCommandsCount)
		, CommandsEncoded(0)
	{
		// Alloc data for command buffer data
		FGPUCommandSignatureDx12 * GPUCommandSignatureDx12 = static_cast<FGPUCommandSignatureDx12*>(GetGPUCommandSignature().get());
		TI_ASSERT(GPUCommandSignatureDx12->GetCommandStrideInBytes() != 0);
		CommandBufferData = ti_new TStream(GPUCommandSignatureDx12->GetCommandStrideInBytes() * InCommandsCount);
	}

	FGPUCommandBufferDx12::~FGPUCommandBufferDx12()
	{
		CommandBufferData = nullptr;
	}

	uint32 FGPUCommandBufferDx12::GetEncodedCommandsCount() const
	{
		return CommandsEncoded;
	}

	void FGPUCommandBufferDx12::EncodeSetMeshBuffer(
		uint32 CommandIndex,
		uint32 ArgumentIndex,
		FMeshBufferPtr MeshBuffer, 
		FInstanceBufferPtr InstanceBuffer)
	{
		FGPUCommandSignatureDx12 * GPUCommandSignatureDx12 = static_cast<FGPUCommandSignatureDx12*>(GetGPUCommandSignature().get());
		TI_ASSERT(GPUCommandSignatureDx12->GetCommandStrideInBytes() != 0);
		FMeshBufferDx12 * MBDx12 = static_cast<FMeshBufferDx12*>(MeshBuffer.get());
		FInstanceBufferDx12 * IBDx12 = static_cast<FInstanceBufferDx12*>(InstanceBuffer.get());
		// Only support indexed triangle list.
		TI_ASSERT(MeshBuffer->GetPrimitiveType() == EPT_TRIANGLELIST);

		// Mesh Buffer will encode 3 D3D12 commands, set vertex buffer, set instance buffer, set index buffer
		const TVector<E_GPU_COMMAND_TYPE>& CommandStructure = GPUCommandSignatureDx12->GetCommandStructure();
		E_GPU_COMMAND_TYPE CommandType = CommandStructure[ArgumentIndex];
		TI_ASSERT(CommandType == GPU_COMMAND_SET_MESH_BUFFER);
		uint32 CommandPos = CommandIndex * GPUCommandSignatureDx12->GetCommandStrideInBytes() + GPUCommandSignatureDx12->GetArgumentStrideOffset(ArgumentIndex);
		// Vertex buffer
		{
			CommandBufferData->Seek(CommandPos);
			CommandBufferData->Set(&MBDx12->VertexBufferView, sizeof(D3D12_VERTEX_BUFFER_VIEW));
			CommandPos += sizeof(D3D12_VERTEX_BUFFER_VIEW);
		}
		// Instance buffer
		{
			CommandBufferData->Seek(CommandPos);
			CommandBufferData->Set(&IBDx12->InstanceBufferView, sizeof(D3D12_VERTEX_BUFFER_VIEW));
			CommandPos += sizeof(D3D12_VERTEX_BUFFER_VIEW);
		}
		// Index buffer
		{
			CommandBufferData->Seek(CommandPos);
			CommandBufferData->Set(&MBDx12->IndexBufferView, sizeof(D3D12_INDEX_BUFFER_VIEW));
			CommandPos += sizeof(D3D12_INDEX_BUFFER_VIEW);
		}
		// Remember commands encoded
		CommandsEncoded = ti_max(CommandsEncoded, CommandIndex);
	}

	void FGPUCommandBufferDx12::EncodeSetDrawIndexed(
		uint32 CommandIndex,
		uint32 ArgumentIndex,
		uint32 IndexCountPerInstance,
		uint32 InstanceCount,
		uint32 StartIndexLocation,
		uint32 BaseVertexLocation,
		uint32 StartInstanceLocation)
	{
		FGPUCommandSignatureDx12 * GPUCommandSignatureDx12 = static_cast<FGPUCommandSignatureDx12*>(GetGPUCommandSignature().get());
		TI_ASSERT(GPUCommandSignatureDx12->GetCommandStrideInBytes() != 0);

		// Draw index
		const TVector<E_GPU_COMMAND_TYPE>& CommandStructure = GPUCommandSignatureDx12->GetCommandStructure();
		E_GPU_COMMAND_TYPE CommandType = CommandStructure[ArgumentIndex];
		TI_ASSERT(CommandType == GPU_COMMAND_DRAW_INDEXED);
		uint32 CommandPos = CommandIndex * GPUCommandSignatureDx12->GetCommandStrideInBytes() + GPUCommandSignatureDx12->GetArgumentStrideOffset(ArgumentIndex);

		D3D12_DRAW_INDEXED_ARGUMENTS DrawIndexed;
		DrawIndexed.IndexCountPerInstance = IndexCountPerInstance;
		DrawIndexed.InstanceCount = InstanceCount;
		DrawIndexed.StartIndexLocation = StartIndexLocation;
		DrawIndexed.BaseVertexLocation = BaseVertexLocation;
		DrawIndexed.StartInstanceLocation = StartInstanceLocation;

		CommandBufferData->Seek(CommandPos);
		CommandBufferData->Set(&DrawIndexed, sizeof(D3D12_DRAW_INDEXED_ARGUMENTS));
		// Remember commands encoded
		CommandsEncoded = ti_max(CommandsEncoded, CommandIndex);
	}
}
#endif