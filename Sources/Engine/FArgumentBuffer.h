/*
TiX Engine v2.0 Copyright (C) 2018~2019
By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
	class FArgumentBuffer : public FRenderResource
	{
	public:
		FArgumentBuffer(FShaderPtr InShader);
		virtual ~FArgumentBuffer();

		int32 GetArgumentIndex()
		{
			return Index;
		}
	protected:

	protected:
		FShaderPtr Shader;
		int32 Index;
	};
}