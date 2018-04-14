// StartUp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TiX.h"

class TestThread : public TThread
{
public:
	TestThread(const TString& Name)
		: TThread(Name)
	{}

	virtual void Run()
	{
		static int32 a = 0;
		printf("hello ... %d\n", a++);
		TThread::ThreadSleep(10);
	}
};

int main()
{
	{
		TEngineConfiguration Config;
		Config.Name = "First TiX Test App";
		Config.Width = 1280;
		Config.Height = 720;

		TEngine::InitEngine(Config);

		// Test thread
		TestThread* tt = ti_new TestThread("TestTixThreadddd");
		tt->Start();

		// Start Loop
		TEngine::Get()->Start();

		// When quit
		tt->Stop();
		ti_delete tt;
	}

	_CrtDumpMemoryLeaks();

    return 0;
}

