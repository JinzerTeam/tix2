/*
	TiX Engine v2.0 Copyright (C) 2018~2019
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"
#include "GPUInstanceOcclusionCullCS.h"
#include "SceneMetaInfos.h"
#include "HiZDownSampleCS.h"

FGPUInstanceOcclusionCullCS::FGPUInstanceOcclusionCullCS()
	: FComputeTask("S_InstanceOcclusionCullCS")
	, InstancesNeedToCull(0)
{
}

FGPUInstanceOcclusionCullCS::~FGPUInstanceOcclusionCullCS()
{
}

void FGPUInstanceOcclusionCullCS::PrepareResources(FRHI * RHI, const vector2di& RTSize, FTexturePtr HiZTexture)
{
	OcclusionInfo = ti_new FOcclusionInfo;
	OcclusionInfo->UniformBufferData[0].RTSize = FUInt4(RTSize.X, RTSize.Y, FHiZDownSampleCS::HiZLevels, 0);
	ResourceTable = RHI->CreateRenderResourceTable(6, EHT_SHADER_RESOURCE);

	ResourceTable->PutTextureInTable(HiZTexture, 4);
}

void FGPUInstanceOcclusionCullCS::UpdateComputeArguments(
	FRHI * RHI,
	const FMatrix& ViewProjection,
	FUniformBufferPtr PrimitiveBBoxes,
	FUniformBufferPtr InstanceMetaInfo,
	FInstanceBufferPtr SceneInstanceData,
	FUniformBufferPtr InFrustumCullResult,
	uint32 InstancesCountIntersectWithFrustum
)
{
	if (VisibilityResult == nullptr || VisibilityResult->GetElements() != InstanceMetaInfo->GetElements())
	{
		// Create visibility buffer to save tile visibility result
		VisibilityResult = RHI->CreateUniformBuffer(sizeof(uint32), InstanceMetaInfo->GetElements(), UB_FLAG_COMPUTE_WRITABLE);
		RHI->UpdateHardwareResourceUB(VisibilityResult, nullptr);
	}

	OcclusionInfo->UniformBufferData[0].ViewProjection = ViewProjection;
	OcclusionInfo->InitUniformBuffer(UB_FLAG_INTERMEDIATE);

	ResourceTable->PutUniformBufferInTable(PrimitiveBBoxes, 0);
	ResourceTable->PutUniformBufferInTable(InstanceMetaInfo, 1);
	ResourceTable->PutInstanceBufferInTable(SceneInstanceData, 2);
	ResourceTable->PutUniformBufferInTable(InFrustumCullResult, 3);
	// t4 is HiZTexture, already set in PrepareResource()
	ResourceTable->PutUniformBufferInTable(VisibilityResult, 5);

	FrustumCullResult = InFrustumCullResult;
	InstancesNeedToCull = InstancesCountIntersectWithFrustum;
}

void FGPUInstanceOcclusionCullCS::Run(FRHI * RHI)
{
	const uint32 BlockSize = 128;
	//const uint32 DispatchSize = (VisibilityResult->GetElements() + (BlockSize - 1)) / BlockSize;
	const uint32 DispatchSize = (InstancesNeedToCull + BlockSize - 1) / BlockSize;

	if (FrustumCullResult != nullptr)
	{
		RHI->CopyBufferRegion(VisibilityResult, 0, FrustumCullResult, VisibilityResult->GetTotalBufferSize());

		RHI->SetComputePipeline(ComputePipeline);
		RHI->SetComputeBuffer(0, OcclusionInfo->UniformBuffer);
		RHI->SetComputeResourceTable(1, ResourceTable);

		RHI->DispatchCompute(vector3di(BlockSize, 1, 1), vector3di(DispatchSize, 1, 1));
	}
}
