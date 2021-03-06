/*
	TiX Engine v2.0 Copyright (C) 2018~2021
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"
#include "GPUTileFrustumCullCS.h"
#include "SceneMetaInfos.h"

//FGPUTileFrustumCullCS::FGPUTileFrustumCullCS()
//	: FComputeTask("S_TileFrustumCullCS")
//{
//}
//
//FGPUTileFrustumCullCS::~FGPUTileFrustumCullCS()
//{
//	ResourceTable = nullptr;
//}
//
//void FGPUTileFrustumCullCS::PrepareResources(FRHI * RHI)
//{
//	// Create visibility buffer to save tile visibility result
//	VisibilityResult = RHI->CreateUniformBuffer(sizeof(uint32), MAX_SCENE_TILE_META_NUM, UB_FLAG_COMPUTE_WRITABLE);
//	RHI->UpdateHardwareResourceUB(VisibilityResult, nullptr);
//
//	// Resource table for Compute cull shader
//	ResourceTable = RHI->CreateRenderResourceTable(2, EHT_SHADER_RESOURCE);
//}
//
//void FGPUTileFrustumCullCS::UpdateComputeArguments(FRHI * RHI, FUniformBufferPtr SceneTileMetaInfoUniformBuffer, FUniformBufferPtr InFrustumUniform)
//{
//	TI_TODO("Does this resource table, need to re-create?");
//	ResourceTable->PutUniformBufferInTable(SceneTileMetaInfoUniformBuffer, 0);
//	ResourceTable->PutUniformBufferInTable(VisibilityResult, 1);
//
//	FrustumUniform = InFrustumUniform;
//}
//
//void FGPUTileFrustumCullCS::Run(FRHI * RHI)
//{
//	const uint32 BlockSize = 128;
//	const uint32 DispatchSize = MAX_SCENE_TILE_META_NUM / BlockSize;
//
//	if (FrustumUniform != nullptr)
//	{
//		RHI->SetComputePipeline(ComputePipeline);
//		RHI->SetComputeBuffer(0, FrustumUniform);
//		RHI->SetComputeResourceTable(1, ResourceTable);
//
//		RHI->DispatchCompute(vector3di(BlockSize, 1, 1), vector3di(DispatchSize, 1, 1));
//	}
//}
