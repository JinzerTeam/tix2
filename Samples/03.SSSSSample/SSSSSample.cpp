// SSSSSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SSSSTicker.h"
#include "SSSSRenderer.h"

void SetupScene()
{
	const TString TargetMeshRes = "head.tres";
	TResourcePtr MeshRes = TResourceLibrary::Get()->LoadResource(TargetMeshRes);
	TMeshBufferPtr MeshBuffer = static_cast<TMeshBuffer*>(MeshRes.get());
	
	// Add these to TScene
	TEngine::Get()->GetScene()->AddStaticMesh(MeshBuffer, MeshBuffer->GetDefaultMaterial(), false, false);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(-1);
	{
		TEngineDesc Desc;
		Desc.Name = "SSSS Sample App";
		Desc.Width = 1280;
		Desc.Height = 720;

		TEngine::InitEngine(Desc);

		// before tick and render
		TEngine::Get()->AddTicker(ti_new TSSSSTicker());
		TEngine::Get()->AddRenderer(ti_new FSSSSRenderer());

		// Setup scenes
		SetupScene();

		// start tick and render

		// Start Loop
		TEngine::Get()->Start();
	}
    return 0;
}

