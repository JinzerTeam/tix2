// SSSSSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SSSSTicker.h"
#include "SSSSRenderer.h"

void SetupScene()
{
	const TString TargetMeshRes = "SM_Head.tres";
	TResourcePtr MeshRes = TResourceLibrary::Get()->LoadResource(TargetMeshRes);
	TMeshBufferPtr MeshBuffer = static_cast<TMeshBuffer*>(MeshRes.get());
	
	TScene * Scene = TEngine::Get()->GetScene();
	// Add mesh to TScene
	Scene->AddStaticMesh(MeshBuffer, MeshBuffer->GetDefaultMaterial(), false, false);

	// Add lights to TScene
	static const int32 N_LIGHTS = 3;
	static const vector3df LightPosition[N_LIGHTS] = {
		vector3df(1.872f, 0.39552f, 0.018f),
		vector3df(1.91f, 1.862472f, -1.838f),
		vector3df(-0.76645f, 0.518553f, 1.773f)
	};
	static const SColor LightColor[N_LIGHTS] = {
		SColor(255, 255, 255, 255),
		SColor(255, 255, 255, 255),
		SColor(255, 255, 255, 255)
	};
	static const float LightIntensity[N_LIGHTS] = {
		1.05f , 0.55f, 1.55f
	};
	for (int32 l = 0; l < 1; ++l)
	{
		Scene->AddLight(LightPosition[l], LightIntensity[l], LightColor[l]);
	}

	// Setup Camera
	TNodeCamera* Camera = Scene->GetActiveCamera();
	Camera->SetPosition(vector3df(-0.72f, -1.14f, 0.47f));
	//Camera->SetPosition(vector3df(2.642f, 0.0277f, -1.623f));
	Camera->SetTarget(vector3df(0.f, 0.f, 0.45f));
	//Camera->SetTarget(vector3df(-0.0078f, 0.07f, -0.015f));
	Camera->SetFOV(DEG_TO_RAD(40));
	Camera->SetNearValue(0.1f);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(-1);
	{
		TEngineDesc Desc;
		Desc.Name = "SSSS Sample App";
		Desc.Width = 1600;
		Desc.Height = 900;

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

