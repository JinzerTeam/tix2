/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"
#include "SSSSRenderer.h"

FSSSSRenderer::FSSSSRenderer()
{
	// Render target test case
	TRenderTargetPtr RT = TRenderTarget::Create(1280, 720);
	RT->AddTextureAttachment(EPF_RGBA8, ERTA_COLOR0);
	RT->Compile();
}

FSSSSRenderer::~FSSSSRenderer()
{
}