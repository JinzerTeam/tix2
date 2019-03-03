/*
	TiX Engine v2.0 Copyright (C) 2018~2019
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
	enum E_RESOURCE_FAMILY
	{
		ERF_Dx12,
		ERF_Metal,
		ERF_Vulkan
	};

	enum E_INDEX_TYPE 
	{
		EIT_16BIT,
		EIT_32BIT,
        
        EIT_COUNT,
	};

	enum E_VERTEX_STREAM_SEGMENT
	{
		EVSSEG_POSITION		= 1,
		EVSSEG_NORMAL		= EVSSEG_POSITION << 1,
		EVSSEG_COLOR		= EVSSEG_NORMAL << 1,
		EVSSEG_TEXCOORD0	= EVSSEG_COLOR << 1,
		EVSSEG_TEXCOORD1	= EVSSEG_TEXCOORD0 << 1,
		EVSSEG_TANGENT		= EVSSEG_TEXCOORD1 << 1,
		EVSSEG_BLENDINDEX	= EVSSEG_TANGENT << 1,
		EVSSEG_BLENDWEIGHT	= EVSSEG_BLENDINDEX << 1,

		EVSSEG_TOTAL		= EVSSEG_BLENDWEIGHT,
	};

	enum E_MESH_STREAM_INDEX
	{
		ESSI_POSITION		= 0,
		ESSI_NORMAL,
		ESSI_COLOR,
		ESSI_TEXCOORD0,
		ESSI_TEXCOORD1,
		ESSI_TANGENT,
		ESSI_BLENDINDEX,
		ESSI_BLENDWEIGHT,

		ESSI_TOTAL,
	};

	enum E_PRIMITIVE_TYPE
	{
		EPT_POINTLIST,
		EPT_LINES,
		EPT_LINESTRIP,
		EPT_TRIANGLELIST,
		EPT_TRIANGLESTRIP,

		EPT_COUNT
	};

	enum E_RENDER_RESOURCE_HEAP_TYPE
	{
		EHT_NONE = -1,
		EHT_RENDERTARGET = 0,
		EHT_DEPTHSTENCIL,
		EHT_SAMPLER,
		EHT_SHADER_RESOURCE,	// Constants, Buffers, Textures and UAV

		EHT_COUNT,
	};
}
