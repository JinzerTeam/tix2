/*
	TiX Engine v2.0 Copyright (C) 2018~2019
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"
#include "GPUComputeUniforms.h"
#include "GPUClusterCullCS.h"
#include "HiZDownSampleCS.h"

FGPUClusterCullCS::FGPUClusterCullCS()
	: FComputeTask("S_ClusterCullCS")
{
}

FGPUClusterCullCS::~FGPUClusterCullCS()
{
}

void FGPUClusterCullCS::PrepareResources(FRHI * RHI, const vector2di& RTSize, FTexturePtr HiZTexture, FUniformBufferPtr VisibleInstanceClusters)
{
	CullUniform = ti_new FCullUniform;
	CullUniform->UniformBufferData[0].RTSize = FUInt4(RTSize.X, RTSize.Y, FHiZDownSampleCS::HiZLevels, 0);

	ResourceTable = RHI->CreateRenderResourceTable(5, EHT_SHADER_RESOURCE);
	ResourceTable->PutUniformBufferInTable(VisibleInstanceClusters, 2);
	ResourceTable->PutTextureInTable(HiZTexture, 3);

	// Create a command buffer that big enough for triangle culling
	VisibleClusters = RHI->CreateUniformBuffer(sizeof(uint32) * 4, 10 * 1024, UB_FLAG_COMPUTE_WRITABLE | UB_FLAG_COMPUTE_WITH_COUNTER);
	VisibleClusters->SetResourceName("VisibleClusters");
	RHI->UpdateHardwareResourceUB(VisibleClusters, nullptr);
	TI_TODO("Change TriangleCullCommands to CommandBuffer as follows");
	//const uint32 TotalInstances = SceneMetaInfo->GetSceneInstancesAdded();
	//TriangleCullCommands = RHI->CreateGPUCommandBuffer(GPUCommandSignature, TotalInstances, UB_FLAG_GPU_COMMAND_BUFFER_RESOURCE | UB_FLAG_COMPUTE_WRITABLE | UB_FLAG_COMPUTE_WITH_COUNTER);
	//TriangleCullCommands->SetResourceName("ProcessedCB");
	//// Add binding arguments
	//TriangleCullCommands->AddVSPublicArgument(0, Scene->GetViewUniformBuffer()->UniformBuffer);
	//RHI->UpdateHardwareResourceGPUCommandBuffer(TriangleCullCommands);
	ResourceTable->PutUniformBufferInTable(VisibleClusters, 4);

	// Create counter reset
	CounterReset = ti_new FCounterReset;
	CounterReset->UniformBufferData[0].Zero = 0;
	CounterReset->InitUniformBuffer(UB_FLAG_INTERMEDIATE);

	// Init GPU command buffer
	TVector<E_GPU_COMMAND_TYPE> CommandStructure;
	CommandStructure.reserve(1);
	CommandStructure.push_back(GPU_COMMAND_DISPATCH);

	GPUCommandSignature = RHI->CreateGPUCommandSignature(ComputePipeline, CommandStructure);
	GPUCommandSignature->SetResourceName("ClusterCullSig");
	RHI->UpdateHardwareResourceGPUCommandSig(GPUCommandSignature);
	
	GPUCommandBuffer = RHI->CreateGPUCommandBuffer(GPUCommandSignature, 1, UB_FLAG_GPU_COMMAND_BUFFER_RESOURCE | UB_FLAG_COMPUTE_WRITABLE | UB_FLAG_COMPUTE_WITH_COUNTER);
	GPUCommandBuffer->SetResourceName("ClusterCullIndirectCommand");
	RHI->UpdateHardwareResourceGPUCommandBuffer(GPUCommandBuffer);
}

void FGPUClusterCullCS::UpdateComputeArguments(
	FRHI * RHI,
	const vector3df& ViewDir,
	const FMatrix& ViewProjection,
	const SViewFrustum& InFrustum,
	FUniformBufferPtr ClusterMetaData,
	FInstanceBufferPtr SceneInstanceData
)
{
	CullUniform->UniformBufferData[0].ViewDir = ViewDir;
	CullUniform->UniformBufferData[0].ViewProjection = ViewProjection;
	for (int32 i = SViewFrustum::VF_FAR_PLANE; i < SViewFrustum::VF_PLANE_COUNT; ++i)
	{
		CullUniform->UniformBufferData[0].Planes[i] = FFloat4(
			InFrustum.Planes[i].Normal.X,
			InFrustum.Planes[i].Normal.Y,
			InFrustum.Planes[i].Normal.Z,
			InFrustum.Planes[i].D);
	}
	CullUniform->InitUniformBuffer(UB_FLAG_INTERMEDIATE);

	ResourceTable->PutUniformBufferInTable(ClusterMetaData, 0);
	ResourceTable->PutInstanceBufferInTable(SceneInstanceData, 1);
	// t2 is VisibleClusters, alrealy set in PrepareResource()
	// t3 is HiZTexture, already set in PrepareResource()
	// u0 is VisibleClusters, already set in PrepareResource()
}

void FGPUClusterCullCS::Run(FRHI * RHI)
{
	const uint32 BlockSize = 128;

	// Reset command buffer counter
	RHI->ComputeCopyBuffer(
		VisibleClusters,
		VisibleClusters->GetCounterOffset(),
		CounterReset->UniformBuffer,
		0,
		sizeof(uint32));

	RHI->SetResourceStateCB(GPUCommandBuffer, RESOURCE_STATE_INDIRECT_ARGUMENT);

	RHI->SetComputePipeline(ComputePipeline);
	RHI->SetComputeBuffer(0, CullUniform->UniformBuffer);
	RHI->SetComputeResourceTable(1, ResourceTable);

	RHI->ExecuteGPUComputeCommands(GPUCommandBuffer);
	//RHI->DispatchCompute(vector3di(BlockSize, 1, 1), vector3di(80, 1, 1));
}