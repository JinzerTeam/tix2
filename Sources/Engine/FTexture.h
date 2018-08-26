/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
	class FTexture : public FRenderResource
	{
	public:
		FTexture(E_RESOURCE_FAMILY InFamily);
		FTexture(E_RESOURCE_FAMILY InFamily, const TTextureDesc& Desc);
		virtual ~FTexture();

		virtual void Destroy() override {};

		void InitTextureInfo(TTexturePtr Texture);

		const TTextureDesc& GetDesc() const
		{
			return TextureDesc;
		}

		int32 GetWidth() const
		{
			return TextureDesc.Width;
		}
		int32 GetHeight() const
		{
			return TextureDesc.Height;
		}

	protected:
		TTextureDesc TextureDesc;


	protected:
	};
}
