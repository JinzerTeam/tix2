/*
	TiX Engine v2.0 Copyright (C) 2018~2021
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once
#include "GPUComputeUniforms.h"

namespace tix
{
	//// MinEdge.w is 1 means this tile info is valid, 0 for empty data
	//#define MAX_SCENE_TILE_META_NUM (256)
	//BEGIN_UNIFORM_BUFFER_STRUCT_ARRAY(FSceneTileMetaInfo, MAX_SCENE_TILE_META_NUM)
	//	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FFloat4, MinEdge)
	//	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FFloat4, MaxEdge)
	//END_UNIFORM_BUFFER_STRUCT(FSceneTileMetaInfo)


	class FSceneMetaInfos
	{
	public:
		FSceneMetaInfos();
		~FSceneMetaInfos();

		void DoSceneTileCulling(FScene * Scene, const SViewFrustum& ViewFrustum);
		void CollectSceneMetaInfos(FScene * Scene);
		void CollectMeshBuffers(FScene * Scene);
		void CollectInstanceBuffers(FScene * Scene);
		void CollectClusterMetaBuffers(FScene * Scene);
		void ClearMetaFlags();
		void UpdateGPUResources();

		enum FSceneMetaFlag
		{
			MetaFlag_SceneTileMetaDirty = 1 << 0,
			MetaFlag_ScenePrimitiveMetaDirty = 1 << 1,
			MetaFlag_SceneInstanceMetaDirty = 1 << 2,
			MetaFlag_SceneClusterMetaDirty = 1 << 3,
			MetaFlag_SceneMeshBufferDirty = 1 << 4,
		};
		bool HasMetaFlag(uint32 InMetaFlag) const
		{
			return (SceneMetaFlags & InMetaFlag) != 0;
		}
		bool IsPrimitiveDataReady() const
		{
			// Bad fix!
			return ScenePrimitiveBBoxes != nullptr && ScenePrimitiveBBoxes->UniformBuffer != nullptr;
		}
		FScenePrimitiveBBoxesPtr GetPrimitiveBBoxesUniform()
		{
			return ScenePrimitiveBBoxes;
		}
		FSceneInstanceMetaInfoPtr GetInstanceMetaUniform()
		{
			return SceneInstancesMetaInfo;
		}
		FMeshBufferPtr GetMergedSceneMeshBuffer()
		{
			return MergedMeshBuffer;
		}
		FInstanceBufferPtr GetMergedInstanceBuffer()
		{
			return MergedInstanceBuffer;
		}
		FUniformBufferPtr GetMergedClusterData()
		{
			return MergedClusterBoundingData;
		}
		FUniformBufferPtr GetMergedSceneMeshBufferInfo()
		{
			return MergedSceneMeshBufferInfo->UniformBuffer;
		}
		uint32 GetSceneInstancesAdded() const
		{
			return SceneInstancesAdded;
		}
		uint32 GetSceneInstancesIntersected() const
		{
			return SceneInstancesIntersected;
		}
		uint32 GetScenePrimitivesAdded() const
		{
			return ScenePrimitivesAdded;
		}
		bool IsTileVisible(const vector2di& TilePos)
		{
			return SceneTileVisibleInfo[TilePos] != ECR_OUTSIDE;
		}
		const TVector<vector2di>& GetSortedTilePositions() const
		{
			return SortedTilePositions;
		}

	private:


	private:
		uint32 SceneMetaFlags;

		// Scene tile meta info
		//FSceneTileMetaInfoPtr SceneTileMetaInfo;
		THMap<vector2di, uint32> SceneTileVisibleInfo;
		
		// Instances Count that added to scene from visible scene tiles
		uint32 SceneInstancesAdded;
		// Instances Count from scene tiles which intersects with view frustum 
		// (instances from scene tiles inner frustum do not need GPU cull calculation, since they are always visible.) 
		uint32 SceneInstancesIntersected;
		// Primitives count that added to scene from visible scene tiles
		// Each primitive is a mesh section
		uint32 ScenePrimitivesAdded;

		TVector<vector2di> SortedTilePositions;

		// Scene tiles count that intersects with frustum
		uint32 SceneTileIntersected;
		// Scene tiles count that totally in frustum
		uint32 SceneTileInner;
		// Scene tile primitive count infos map.
		// Key is tile position, value is {PritmivesCount, PrimitivesOffset in ScenePrimitiveBBox, InstancesCount, InstancesOffset in SceneInstancesMetaInfo};
		THMap<vector2di, FUInt4> ActiveSceneTileInfoMap;

		// Scene Instances info
		FSceneInstanceMetaInfoPtr SceneInstancesMetaInfo;
		FInstanceBufferPtr MergedInstanceBuffer;

		// Scene Meshbuffer info
		FMeshBufferPtr MergedMeshBuffer;
		FSceneMeshBufferInfoPtr MergedSceneMeshBufferInfo;

		// Scene mesh cluster info
		FUniformBufferPtr MergedClusterBoundingData;
		FClusterMetaInfoPtr ClusterMetaData;

		// Scene primitive meta info
		FScenePrimitiveBBoxesPtr ScenePrimitiveBBoxes;

		friend class FScene;
	};
} // end namespace tix
