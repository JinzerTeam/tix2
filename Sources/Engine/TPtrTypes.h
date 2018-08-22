/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
#define DECLARE_INSTRUSIVE_PTR(ClassName) \
	class ClassName; \
	typedef TI_INTRUSIVE_PTR(ClassName) ClassName##Ptr

	DECLARE_INSTRUSIVE_PTR(TResFile);
	DECLARE_INSTRUSIVE_PTR(TStream);
	DECLARE_INSTRUSIVE_PTR(TMaterial);
	DECLARE_INSTRUSIVE_PTR(TMaterialInstance);
	DECLARE_INSTRUSIVE_PTR(TMeshBuffer);
	DECLARE_INSTRUSIVE_PTR(TResource);
	DECLARE_INSTRUSIVE_PTR(TPipeline);
	DECLARE_INSTRUSIVE_PTR(TTexture);
	DECLARE_INSTRUSIVE_PTR(FRenderResource);
	DECLARE_INSTRUSIVE_PTR(FTexture);
	DECLARE_INSTRUSIVE_PTR(FPipeline);
	DECLARE_INSTRUSIVE_PTR(FMeshBuffer);
	DECLARE_INSTRUSIVE_PTR(FPrimitive);
	DECLARE_INSTRUSIVE_PTR(FUniformBuffer);
} // end namespace tix
