/*
	TiX Engine v2.0 Copyright (C) 2018~2019
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
	// TMeshBuffer, hold mesh vertex and index data memory in game thread
	class TMeshBuffer : public TResource
	{
	public:
		TMeshBuffer();
		~TMeshBuffer();

		static const TI_API int32 SemanticSize[ESSI_TOTAL];
		static const TI_API int8* SemanticName[ESSI_TOTAL];

	public:
		FMeshBufferPtr MeshBufferResource;

		static int32 GetStrideFromFormat(uint32 Format);
		static TVector<E_MESH_STREAM_INDEX> GetSteamsFromFormat(uint32 Format);

		virtual void InitRenderThreadResource() override;
		virtual void DestroyRenderThreadResource() override;

		void SetVertexStreamData(
			uint32 InFormat,
			const void* InVertexData, int32 InVertexCount,
			E_INDEX_TYPE InIndexType,
			const void* InIndexData, int32 InIndexCount);

		int32 GetVerticesCount() const
		{
			return VsDataCount;
		}

		int32 GetIndicesCount() const
		{
			return PsDataCount;
		}

		E_PRIMITIVE_TYPE GetPrimitiveType() const
		{
			return PrimitiveType;
		}

		E_INDEX_TYPE GetIndexType() const
		{
			return IndexType;
		}

		int32 GetUsage() const
		{
			return Usage;
		}

		uint32 GetFlag() const
		{
			return MeshFlag;
		}

		void SetPrimitiveType(E_PRIMITIVE_TYPE type)
		{
			PrimitiveType = type;
		}

		uint32 GetVSFormat() const
		{
			return VsFormat;
		}

		uint32 GetStride() const
		{
			return Stride;
		}

		const aabbox3df& GetBBox() const
		{
			return BBox;
		}

		void SetBBox(const aabbox3df& bbox)
		{
			BBox = bbox;
		}

		const void* GetVSData() const
		{
			return VsData;
		}

		const void* GetPSData() const
		{
			return PsData;
		}

		void SetDefaultMaterial(TMaterialInstancePtr Material)
		{
			DefaultMaterial = Material;
		}

		TMaterialInstancePtr GetDefaultMaterial()
		{
			return DefaultMaterial;
		}
	protected:

	protected:
		E_PRIMITIVE_TYPE PrimitiveType;
		int32 Usage;
		aabbox3df BBox;

		uint32 MeshFlag;

		uint8* VsData;
		int32 VsDataCount;

		E_INDEX_TYPE IndexType;
		uint8* PsData;
		int32 PsDataCount;

		uint32 VsFormat;
		uint32 Stride;

		TMaterialInstancePtr DefaultMaterial;
	};
}
