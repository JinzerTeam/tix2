/*
	TiX Engine v2.0 Copyright (C) 2018~2019
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once
#include "SceneMetaInfos.h"
#include "HiZDownSampleCS.h"
#include "InstanceFrustumCullCS.h"

class FGPUDrivenRenderer : public FDefaultRenderer
{
public:
	FGPUDrivenRenderer();
	virtual ~FGPUDrivenRenderer();

	static FGPUDrivenRenderer* Get();

	virtual void InitInRenderThread() override;
	virtual void InitRenderFrame(FScene* Scene) override;
	virtual void Render(FRHI* RHI, FScene* Scene) override;

	void UpdateFrustumUniform(const SViewFrustum& Frustum);

private:
	void TestDrawSceneIndirectCommandBuffer(FRHI * RHI, FScene * Scene, FGPUCommandBufferPtr CommandBuffer);

private:
	FSceneMetaInfos * SceneMetaInfo;

	FArgumentBufferPtr AB_Result;

	FFullScreenRender FSRender;
	FRenderTargetPtr RT_BasePass;

	FGPUCommandSignaturePtr GPUCommandSignature;
	FGPUCommandBufferPtr ProcessedGPUCommandBuffer;

	FGPUCommandSignaturePtr PreZGPUCommandSignature;
	FGPUCommandBufferPtr PreZGPUCommandBuffer;
	FGPUCommandBufferPtr ProcessedPreZGPUCommandBuffer;

	SViewFrustum Frustum;
	FCameraFrustumUniformPtr FrustumUniform;

	// Compute Tasks
	FInstanceFrustumCullCSPtr InstanceFrustumCullCS;
};