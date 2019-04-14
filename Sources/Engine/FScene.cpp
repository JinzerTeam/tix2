/*
	TiX Engine v2.0 Copyright (C) 2018~2019
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"
#include "FScene.h"
#include "FSceneLights.h"

namespace tix
{
	FScene::FScene()
		: SceneFlags(0)
	{
		SceneLights = ti_new FSceneLights;
	}

	FScene::~FScene()
	{
		SAFE_DELETE(SceneLights);
	}

	void FScene::SetViewProjection(const FViewProjectionInfo& Info)
	{
		TI_ASSERT(IsRenderThread());
		ViewProjection = Info;
		SetSceneFlag(ViewProjectionDirty, true);
	}

	void FScene::AddPrimitives(const TVector<FPrimitivePtr>& InPrimitives)
	{
		// Send different primitives to different draw list
		TI_ASSERT(IsRenderThread());
		for (auto& P : InPrimitives)
		{
			StaticDrawLists[P->GetDrawList()].push_back(P);
		}
	}

	void FScene::RemovePrimitives(const TVector<FPrimitivePtr>& InPrimitives)
	{
		TI_ASSERT(IsRenderThread());
		TI_TODO("Find a fast way to locate Primitive in draw list.");

		for (auto& P : InPrimitives)
		{
			TVector<FPrimitivePtr>& DrawList = StaticDrawLists[P->GetDrawList()];
			TVector<FPrimitivePtr>::iterator it = tix_find(DrawList.begin(), DrawList.end(), P);
			if (it != DrawList.end())
			{
				DrawList.erase(it);
			}
		}
	}

	void FScene::PrepareViewUniforms()
	{
		if (HasSceneFlag(FScene::ViewProjectionDirty))
		{
			// Always make a new View uniform buffer for on-the-fly rendering
			ViewUniformBuffer = ti_new FViewUniformBuffer();

			const FViewProjectionInfo& VPInfo = GetViewProjection();
			ViewUniformBuffer->UniformBufferData[0].ViewProjection = VPInfo.MatProj * VPInfo.MatView;
			ViewUniformBuffer->UniformBufferData[0].ViewDir = VPInfo.CamDir;
			ViewUniformBuffer->UniformBufferData[0].ViewPos = VPInfo.CamPos;

			ViewUniformBuffer->InitUniformBuffer();

			// remove vp dirty flag
			SetSceneFlag(FScene::ViewProjectionDirty, false);
		}
	}
}
