/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
	BEGIN_UNIFORM_BUFFER_STRUCT(FDynamicLightUniformBuffer, UB_FLAG_DYNAMIC_LIGHT)
		DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FVector4, LightPosition)
		DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FVector4, LightColor)
	END_UNIFORM_BUFFER_STRUCT(FDynamicLightUniformBuffer)

	class FLight : public IReferenceCounted
	{
	public:
		FLight(TNodeLight * Light);
		~FLight();

		FDynamicLightUniformBufferPtr DynamicLightBuffer;
	protected:
		void InitFromLightNode(TNodeLight * Light);
	};
} // end namespace tix

