// StartUp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TiX.h"

class MyTestThread : public TThread
{
public:
	MyTestThread(const TString& Name)
		: TThread(Name)
	{}

	virtual void Run()
	{
		static int32 a = 0;
		printf("MyTestThread says hello ... %d\n", a++);
		TThread::ThreadSleep(10);
	}
};

void TestNormalRun()
{
	// Start Loop
	TEngine::Get()->Start();
}

void TestThread()
{
	// Test thread
	MyTestThread* tt = ti_new MyTestThread("TestTixThreadddd");
	tt->Start();

	// Start Loop
	TEngine::Get()->Start();

	// When quit
	tt->Stop();
	ti_delete tt;
}
class MyTestTaskThread : public TTaskThread
{
public:
	MyTestTaskThread(const TString& Name)
		: TTaskThread(Name)
	{}
};

class MyTestTask : public TTask
{
	virtual void Execute()
	{
		static int32 aa = 0;
		_LOG(Log, "Task index: %d\n", aa++);
	}
};
void TestTask()
{
	// Test task thread
	MyTestTaskThread* tt = ti_new MyTestTaskThread("TestTaskThread");
	tt->Start();

	for (int32 i = 0; i < 4; ++i)
	{
		MyTestTask* task1 = ti_new MyTestTask;
		tt->AddTask(task1);
	}

	// Start Loop
	TEngine::Get()->Start();

	// When quit
	tt->Stop();
	ti_delete tt;
}

#include <sstream>
class TMyTicker : public TTicker
{
public:
	virtual void Tick(float Dt)
	{
		_LOG(Log, "TMyTestTicker is Ticking, Dt is %f.\n", Dt);

		TScene * Scene = TEngine::Get()->GetScene();
		Scene->UpdateAllNodesTransforms();
	}
};

class FMyTestRenderer : public FDefaultRenderer
{
public:
	virtual void Render(FRHI * RHI, FScene * Scene) override
	{
		_LOG(Log, "My Test Renderer is rendering.\n");
		FDefaultRenderer::Render(RHI, Scene);
	}
};

void TestTickerAndRenderer()
{
	TEngine::Get()->AddTicker(ti_new TMyTicker());
	TEngine::Get()->AddRenderer(ti_new FMyTestRenderer());

	// Start Loop
	TEngine::Get()->Start();
}

void TestTixResfileLoading()
{
	//return;
	const TString TargetMeshRes = "../../Content/head.tix";
	TResourcePtr meshbuffer = TResourceLibrary::Get()->LoadResource(TargetMeshRes);

	const TString TargetTextureRes = "../../Content/DiffuseMap.tix";
	TResourcePtr texture = TResourceLibrary::Get()->LoadResource(TargetTextureRes);

	const TString TargetMI = "../../Content/MaterialInstanceTest.tix";
	TResourcePtr MInstance = TResourceLibrary::Get()->LoadResource(TargetMI);

	meshbuffer = nullptr;
	texture = nullptr;
}

void TestRenderMesh()
{
	TestTixResfileLoading();

	const TString TargetMeshRes = "../../Content/head.tix";
	TResourcePtr MeshRes = TResourceLibrary::Get()->LoadResource(TargetMeshRes);
	TMeshBufferPtr MeshBuffer = static_cast<TMeshBuffer*>(MeshRes.get());

	const TString TargetTextureRes = "../../Content/DiffuseMap.tix";
	TResourcePtr TextureRes = TResourceLibrary::Get()->LoadResource(TargetTextureRes);
	TTexturePtr Texture = static_cast<TTexture*>(TextureRes.get());

	const TString TargetMI = "../../Content/MaterialInstanceTest.tix";
	TResourcePtr MInstanceRes = TResourceLibrary::Get()->LoadResource(TargetMI);
	TMaterialInstancePtr MInstance = static_cast<TMaterialInstance*>(MInstanceRes.get());

	// Add these to TScene
	TEngine::Get()->GetScene()->AddStaticMesh(MeshBuffer, MInstance, false, false);
}

void printMatrix(const matrix4& mat)
{
	printf("%f %f %f %f\n", mat[0], mat[1], mat[2], mat[3]);
	printf("%f %f %f %f\n", mat[4], mat[5], mat[6], mat[7]);
	printf("%f %f %f %f\n", mat[8], mat[9], mat[10], mat[11]);
	printf("%f %f %f %f\n======\n", mat[12], mat[13], mat[14], mat[15]);
}

void TestMatrixLHRH()
{
	matrix4 matView = buildCameraLookAtMatrix(vector3df(5, 0, 0), vector3df(), vector3df(0, 0, 1));
	printMatrix(matView);
	matrix4 matProj = buildProjectionMatrixPerspectiveFov(3.14159f / 4.f, 4.f / 3.f, 0.1f, 100.f);
	printMatrix(matProj);
}

int main()
{
	{
		TEngineConfiguration Config;
		Config.Name = "First TiX Test App";
		Config.Width = 1280;
		Config.Height = 720;

		TestMatrixLHRH();

		TEngine::InitEngine(Config);

		// before tick and render
		TestRenderMesh();

		// start tick and render
		//TestNormalRun();
		//TestThread();
		//TestTask();
		TestTickerAndRenderer();
	}

	_CrtDumpMemoryLeaks();

    return 0;
}

