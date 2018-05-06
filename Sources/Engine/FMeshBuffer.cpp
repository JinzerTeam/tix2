/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"

namespace tix
{
	static const int32 SematicSize[ESSI_TOTAL] =
	{
		12,	// ESSI_POSITION,
		12,	// ESSI_NORMAL,		// TI_TODO("May use packed normal in future");
		4,	// ESSI_COLOR,
		8,	// ESSI_TEXCOORD0,	// TI_TODO("May use half float texcoord in future");
		8,	// ESSI_TEXCOORD1,	// TI_TODO("May use half float texcoord in future");
		12,	// ESSI_TANGENT,	// TI_TODO("May use packed tangent in future");
		4,	// ESSI_BLENDINDEX,
		16,	// ESSI_BLENDWEIGHT,// TI_TODO("May use half float blend weight in future");
	};
	FMeshBuffer::FMeshBuffer(E_MB_TYPES type)
		: Type(type)
		, PrimitiveType(EPT_TRIANGLELIST)
		, VsData(nullptr)
		, VsDataCount(0)
		, IndexType(EIT_16BIT)
		, PsData(nullptr)
		, PsDataCount(0)
		, VsFormat(0)
		, Stride(0)
		, MeshFlag(0)
	{
	}

	FMeshBuffer::~FMeshBuffer()
	{
		TI_TODO("Release VsData and PsData");
	}

	void FMeshBuffer::SetVertexStreamData(
		uint32 InFormat,
		void* InVertexData, int32 InVertexCount,
		E_INDEX_TYPE InIndexType, void* InIndexData, int32 InIndexCount)
	{
		VsFormat = InFormat;
		VsDataCount = InVertexCount;

		IndexType = InIndexType;
		PsDataCount = InIndexCount;

		TI_TODO("Align VsData and PsData with 16 bytes.");
		VsData = (uint8*)InVertexData;
		PsData = (uint8*)InIndexData;

		// Calculate stride
		Stride = 0;
		for (UINT seg = 1, i = 0; seg <= EVSSEG_TOTAL; seg <<= 1, ++i)
		{
			if (VsFormat & seg)
			{
				Stride += SematicSize[i];
			}
		}

		//CreateHardwareBuffer();
	}
}