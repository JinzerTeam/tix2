/*
	TiX Engine v2.0 Copyright (C) 2018~2019
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
	enum E_MI_PARAM_TYPE
	{
		MIPT_UNKNOWN,
		MIPT_INT,
		MIPT_FLOAT,
		MIPT_INT4,
		MIPT_FLOAT4,
		MIPT_TEXTURE,

		MIPT_COUNT,
	};

	class TMaterialInstance : public TResource
	{
	public:
		TMaterialInstance();
		virtual ~TMaterialInstance();

		virtual void InitRenderThreadResource() override;
		virtual void DestroyRenderThreadResource() override;

		static int32 GetParamTypeBytes(E_MI_PARAM_TYPE Type);

		TMaterialPtr LinkedMaterial;
		FArgumentBufferPtr ArgumentBuffer;

	protected:

		TVector<TString> ParamNames;
		TVector<int32> ParamTypes;
		TStreamPtr ParamValueBuffer;
#if ENABLE_VT_SYSTEM
		TVector<TString> ParamTextureNames;
		TVector<vector2di> ParamTextureSizes;
#else
		TVector<TTexturePtr> ParamTextures;
#endif

	protected:
		friend class TAssetFile;
	};
}
