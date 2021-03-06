/*
	TiX Engine v2.0 Copyright (C) 2018~2021
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

class FGPUTriangleCullCS : public FComputeTask
{
public:
	FGPUTriangleCullCS();
	virtual ~FGPUTriangleCullCS();

	void PrepareResources(FRHI * RHI, const vector2di& RTSize, FTexturePtr HiZTexture);
	void UpdateComputeArguments(
		FRHI * RHI,
		const vector3df& ViewDir,
		const FMatrix& ViewProjection,
		const SViewFrustum& InFrustum,
		FMeshBufferPtr InSceneMergedMeshBuffer,
		FInstanceBufferPtr SceneInstanceData,
		FUniformBufferPtr SceneMeshBufferInfo,
		FUniformBufferPtr InVisibleClusters,
		FGPUCommandBufferPtr InClusterCommandBuffer);
	virtual void Run(FRHI * RHI) override;

	FUniformBufferPtr GetCulledTriangleIndexBuffer()
	{
		return VisibleTriangleIndex;
	}

	//FGPUCommandBufferPtr GetDispatchCommandBuffer()
	//{
	//	return GPUCommandBuffer;
	//}
private:

private:
	FCullUniformPtr CullUniform;
	FRenderResourceTablePtr ResourceTable;

	FInstanceBufferPtr SceneInstanceData;

	FCounterResetPtr CounterReset;
	FUniformBufferPtr VisibleTriangleIndex;
	FGPUCommandBufferPtr ClusterGPUCommandBufferRef;
	FUniformBufferPtr DebugGroup;

	FUniformBufferPtr VisibleClusters;

	//FGPUCommandSignaturePtr GPUCommandSignature;
	//FGPUCommandBufferPtr GPUCommandBuffer;

};
typedef TI_INTRUSIVE_PTR(FGPUTriangleCullCS) FGPUTriangleCullCSPtr;
