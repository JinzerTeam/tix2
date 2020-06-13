/*
	TiX Engine v2.0 Copyright (C) 2018~2021
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once
#include "HBAOCS.h"

class FGTAORenderer : public FDefaultRenderer
{
public:
	FGTAORenderer();
	virtual ~FGTAORenderer();

	static FGTAORenderer* Get();

	virtual void InitInRenderThread() override;
	virtual void InitRenderFrame(FScene* Scene) override;
	virtual void Render(FRHI* RHI, FScene* Scene) override;

private:
	void DrawSceneTiles(FRHI* RHI, FScene * Scene);

private:
	FArgumentBufferPtr AB_Result;

	FFullScreenRender FSRender;
	FRenderTargetPtr RT_BasePass;

	// AO Compute Shader
	FHBAOCSCSPtr HBAOCompute;
};
