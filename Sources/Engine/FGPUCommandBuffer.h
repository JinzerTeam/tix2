/*
	TiX Engine v2.0 Copyright (C) 2018~2020
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
	// Indirect drawing GPU command buffer
	class FGPUCommandBuffer : public FRenderResource
	{
	public:
		FGPUCommandBuffer(FGPUCommandSignaturePtr Signature, uint32 InCommandsCount, uint32 InBufferFlag);
		virtual ~FGPUCommandBuffer();

		FGPUCommandSignaturePtr GetGPUCommandSignature()
		{
			return GPUCommandSignature;
		}

		TI_API virtual uint32 GetEncodedCommandsCount() const = 0;
		TI_API virtual void EncodeSetVertexBuffer(
			uint32 CommandIndex, 
			uint32 ArgumentIndex,
			FMeshBufferPtr MeshBuffer) = 0;
		TI_API virtual void EncodeSetInstanceBuffer(
			uint32 CommandIndex,
			uint32 ArgumentIndex,
			FInstanceBufferPtr InstanceBuffer) = 0;
		TI_API virtual void EncodeSetIndexBuffer(
			uint32 CommandIndex,
			uint32 ArgumentIndex,
			FMeshBufferPtr MeshBuffer) = 0;
		TI_API virtual void EncodeSetDrawIndexed(
			uint32 CommandIndex,
			uint32 ArgumentIndex,
			uint32 IndexCountPerInstance,
			uint32 InstanceCount,
			uint32 StartIndexLocation,
			uint32 BaseVertexLocation,
			uint32 StartInstanceLocation
		) = 0;

		static const uint32 MAX_BINDING_UNIFORMS = 4;
		TI_API void AddVSPublicArgument(uint32 InBindingIndex, FUniformBufferPtr InUniformBuffer);
		TI_API void AddPSPublicArgument(uint32 InBindingIndex, FUniformBufferPtr InUniformBuffer);

		const TVector<FUniformBufferPtr>& GetVSPublicArguments() const
		{
			return VSPublicArguments;
		}
		const TVector<FUniformBufferPtr>& GetPSPublicArguments() const
		{
			return PSPublicArguments;
		}
		FUniformBufferPtr GetCommandBuffer()
		{
			return CommandBuffer;
		}
	private:

	protected:
		FGPUCommandSignaturePtr GPUCommandSignature;
		TVector<FUniformBufferPtr> VSPublicArguments;
		TVector<FUniformBufferPtr> PSPublicArguments;

		FUniformBufferPtr CommandBuffer;
	};
} // end namespace tix
