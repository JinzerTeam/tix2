/*
	TiX Engine v2.0 Copyright (C) 2018~2020
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"
#include "SceneMetaInfos.h"

namespace tix
{
	FSceneMetaInfos::FSceneMetaInfos()
		: SceneMetaFlags(0)
		, ActiveSceneTileInfos(0)
		, ScenePrimitivesAdded(0)
		, ActiveSceneInstanceInfos(0)
		, ActiveScenePrimitiveBBoxes(0)
	{
		Init();
	}

	FSceneMetaInfos::~FSceneMetaInfos()
	{
		SceneTileMetaInfo = nullptr;
	}

	void FSceneMetaInfos::Init()
	{
		// Create a mesh buffer
		FRHI * RHI = FRHI::Get();

		SceneTileMetaInfo = ti_new FSceneTileMetaInfo;
		SceneTileMetaInfo->InitToZero();
		ActiveSceneTileInfos = 0;

		ScenePrimitiveBBoxes = ti_new FScenePrimitiveBBoxes;
		ScenePrimitiveBBoxes->InitToZero();
		ActiveScenePrimitiveBBoxes = 0;

		SceneInstancesMetaInfo = ti_new FSceneInstanceMetaInfo;
		SceneInstancesMetaInfo->InitToZero();
		ActiveSceneInstanceInfos = 0;
	}

	void FSceneMetaInfos::OnAddPrimitive(FPrimitivePtr InPrimitive)
	{
		FUInt4 PrimitiveInfo;

		ScenePrimitiveBBoxes->UniformBufferData[ActiveScenePrimitiveBBoxes].MinEdge = InPrimitive->GetBBox().MinEdge;
		ScenePrimitiveBBoxes->UniformBufferData[ActiveScenePrimitiveBBoxes].MaxEdge = InPrimitive->GetBBox().MaxEdge;
		++ActiveScenePrimitiveBBoxes;
		TI_ASSERT(ActiveScenePrimitiveBBoxes < MAX_DRAW_CALL_IN_SCENE);

		// Mark primitives as dirty
		SceneMetaFlags |= MetaFlag_ScenePrimitiveMetaDirty;
	}

	void FSceneMetaInfos::OnAddSceneTile(TSceneTileResourcePtr InSceneTileRes)
	{
		const vector2di& TilePos = InSceneTileRes->Position;
		const aabbox3df& TileBBox = InSceneTileRes->BBox;

		// Collect tile meta info data
		SceneTileMetaInfo->UniformBufferData[ActiveSceneTileInfos].MinEdge = FFloat4(TileBBox.MinEdge.X, TileBBox.MinEdge.Y, TileBBox.MinEdge.Z, 1.f);
		SceneTileMetaInfo->UniformBufferData[ActiveSceneTileInfos].MaxEdge = FFloat4(TileBBox.MaxEdge.X, TileBBox.MaxEdge.Y, TileBBox.MaxEdge.Z, 1.f);

		// Remember the meta index of this tile
		uint32 TileIndex = ActiveSceneInstanceInfos;
		++ActiveSceneTileInfos;
		TI_ASSERT(ActiveSceneTileInfos < MAX_SCENE_TILE_META_NUM);

		// Mark tile as dirty
		SceneMetaFlags |= MetaFlag_SceneTileMetaDirty;

		// Collect instance meta info data.
		const TVector<vector2di>& InstancesOffsetAndCount = InSceneTileRes->InstanceOffsetAndCount;
		for ()
		{
			TI_ASSERT(0);
			SceneInstancesMetaInfo->UniformBufferData[ActiveSceneInstanceInfos].Info.X = 0;
			SceneInstancesMetaInfo->UniformBufferData[ActiveSceneInstanceInfos].Info.Y = TileIndex;
			++ActiveSceneInstanceInfos;
			TI_ASSERT(ActiveSceneInstanceInfos < MAX_INSTANCES_IN_SCENE);
		}
		
		// Mark instance as dirty
		SceneMetaFlags |= MetaFlag_SceneInstanceMetaDirty;
	}

	void FSceneMetaInfos::UpdateGPUResources()
	{
		// MetaFlag Clear at FScene::ClearSceneFlags();
		if (HasMetaFlag(MetaFlag_SceneTileMetaDirty))
		{
			SceneTileMetaInfo->InitUniformBuffer();
		}
		if (HasMetaFlag(MetaFlag_ScenePrimitiveMetaDirty))
		{
			ScenePrimitiveBBoxes->InitUniformBuffer();
		}
	}

	void FSceneMetaInfos::ClearMetaFlags()
	{
		SceneMetaFlags = 0;
	}
}
