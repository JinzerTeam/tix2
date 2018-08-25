// SSSSSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TiX.h"


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

		// start tick and render
		TEngine::Get()->AddDefaultRenderer();

		// Start Loop
		TEngine::Get()->Start();
	}
    return 0;
}

