/*
	TiX Engine v2.0 Copyright (C) 2018~2021
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

BEGIN_UNIFORM_BUFFER_STRUCT(FCameraFrustumUniform)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FFloat4, BBoxMin)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FFloat4, BBoxMax)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER_ARRAY(FFloat4, Planes, [6])
END_UNIFORM_BUFFER_STRUCT(FCameraFrustumUniform)


BEGIN_UNIFORM_BUFFER_STRUCT(FOcclusionInfo)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FMatrix, ViewProjection)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FUInt4, RTSize)	// xy = Screen RT Size, z = Max Mips
END_UNIFORM_BUFFER_STRUCT(FOcclusionInfo)


BEGIN_UNIFORM_BUFFER_STRUCT(FCounterReset)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(uint32, Zero)
END_UNIFORM_BUFFER_STRUCT(FCounterReset)

BEGIN_UNIFORM_BUFFER_STRUCT(FViewFrustumUniform)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FFloat4, ViewDir)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FMatrix, ViewProjection)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FUInt4, RTSize)	// xy = Screen RT Size, z = Max Mips
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER_ARRAY(FFloat4, Planes, [6])
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER_ARRAY(FFloat4, Padding, [4])
END_UNIFORM_BUFFER_STRUCT(FViewFrustumUniform)


// Primitive BBox info
//#define MAX_STATIC_MESH_IN_SCENE (2048)
BEGIN_UNIFORM_BUFFER_STRUCT_ARRAY_DYNAMIC(FSceneMeshBBoxes)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FFloat4, MinEdge)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FFloat4, MaxEdge)
END_UNIFORM_BUFFER_STRUCT(FSceneMeshBBoxes)

// Info.x = scene mesh index this instance link to, in FScene::SceneMeshes order, to access scene mesh bbox
// Info.y = if this primitive is loaded. 1 = loaded; 0 = loading
// Info.z = cluster index begin
// Info.w = cluster count
//#define MAX_INSTANCES_IN_SCENE (40 * 1024)
BEGIN_UNIFORM_BUFFER_STRUCT_ARRAY_DYNAMIC(FSceneInstanceMetaInfo)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FUInt4, Info)
END_UNIFORM_BUFFER_STRUCT(FSceneInstanceMetaInfo)

// Info.x = primitive index
BEGIN_UNIFORM_BUFFER_STRUCT_ARRAY_DYNAMIC(FClusterMetaInfo)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FUInt4, Info)
END_UNIFORM_BUFFER_STRUCT(FClusterMetaInfo)

// Info.x = Vertex data offsets in bytes
// Info.y = Index data offsets in bytes
BEGIN_UNIFORM_BUFFER_STRUCT_ARRAY_DYNAMIC(FSceneMeshBufferInfo)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FUInt4, Info)
END_UNIFORM_BUFFER_STRUCT(FSceneMeshBufferInfo)

#define MAX_VISIBLE_INSTANCE_CLUSTERS_COUNT (5 * 1024)
#define MAX_VISIBLE_CLUSTERS_COUNT (2 * 1024)
#define MAX_TRIANGLE_VISIBLE_COUNT (10 * 1024)