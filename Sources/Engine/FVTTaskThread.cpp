/*
	TiX Engine v2.0 Copyright (C) 2018~2019
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"
#include "FVTTaskThread.h"
#include "FVTSystem.h"
#include "TVTTextureLoader.h"

namespace tix
{
	FVTAnalysisThread::FVTAnalysisThread()
		: TThread("VTAnalysisThread")
		, SearchedLocation(0)
		, VTLoadingThread(nullptr)
	{
		// Init Physic pages slots
		PhysicPageTextures.resize(FVTSystem::PPCount);
		for (int32 i = 0; i < FVTSystem::PPCount; ++i)
		{
			PhysicPageTextures[i] = uint32(-1);
		}

		// Start loading thread
		VTLoadingThread = ti_new FVTLoadingThread;
		VTLoadingThread->Start();
	}

	FVTAnalysisThread::~FVTAnalysisThread()
	{
		VTLoadingThread->Stop();
		ti_delete VTLoadingThread;
	}

	void FVTAnalysisThread::Stop()
	{
		if (Thread != nullptr)
		{
			{
				unique_lock<TMutex> CLock(TaskBeginMutex);
				IsRunning = false;
				TaskBeginCond.notify_one();
			}
			Thread->join();

			ti_delete Thread;
			Thread = nullptr;
		}
	}

	void FVTAnalysisThread::Run()
	{
		{
			// wait for begin signal
			unique_lock<TMutex> TaskLock(TaskBeginMutex);
			TaskBeginCond.wait(TaskLock);
		}
		
		{
			TI_ASSERT(Buffers.size() > 0);
			AnalysisBuffer();
			TI_TODO("Analysis time consume");
		}
	}

	void FVTAnalysisThread::AddUVBuffer(TStreamPtr InBuffer)
	{
		unique_lock<TMutex> CLock(TaskBeginMutex);
		TaskBeginCond.notify_one();

		BufferMutex.lock();
		Buffers.push_back(InBuffer);
		BufferMutex.unlock();
	}

	struct FSortTask
	{
		FSortTask(THMap<uint32, FVTSystem::FPageLoadInfo>& InTasks)
			: LoadTasks(InTasks)
		{}

		THMap<uint32, FVTSystem::FPageLoadInfo>& LoadTasks;

		bool operator()(uint32 A, uint32 B)
		{
			return LoadTasks[A] < LoadTasks[B];
		}
	};

	void FVTAnalysisThread::AnalysisBuffer()
	{
		TStreamPtr Buffer;
		{
			BufferMutex.lock();
			Buffer = Buffers.front();
			Buffers.pop_front();
			BufferMutex.unlock();
		}

		FVTSystem * VTSystem = FVTSystem::Get();
		const FFloat4* DataPtr = (const FFloat4*)Buffer->GetBuffer();
		const int32 DataCount = Buffer->GetLength() / sizeof(FFloat4);

		THMap<uint32, uint32> NewPages;	// New pages in this frame
		THMap<uint32, uint32> UsedLocations;	// Used locations in PhysicPageTextures in this frame;

		// Go through every pixel
		for (int32 i = 0 ; i < DataCount ; ++ i)
		{
			const FFloat4& Data = DataPtr[i];
			if (Data.W > 0.f)
			{
				vector2di Position;
				Position.X = (int32)(Data.X * FVTSystem::VTSize);
				Position.Y = (int32)(Data.Y * FVTSystem::VTSize);

				int32 PageX = Position.X / FVTSystem::PPSize;
				int32 PageY = Position.Y / FVTSystem::PPSize;
				TI_ASSERT(PageX >= 0 && PageY >= 0);
				uint32 PageIndex = PageY * FVTSystem::ITSize + PageX;

				if (PhysicPagesMap.find(PageIndex) == PhysicPagesMap.end())
				{
					// This is a page not in Slots, remember it
					NewPages[PageIndex] = 1;
				}
				else
				{
					// Remember this location is used in this frame
					UsedLocations[PhysicPagesMap[PageIndex]] = 1;
				}
			}
		}
		// Pages updated in one frame can not exceed PPCount(1024)
		TI_ASSERT(NewPages.size() + UsedLocations.size() < FVTSystem::PPCount);

		// Insert new pages to Physic Page Slots, and get load info, send Load task
		FVTTaskOrderList* VTTaskOrder = ti_new FVTTaskOrderList();	// Task execute order, point to VTLoadTasks, will be used in VTLoadingThread
		FVTLoadTaskMap* VTLoadTasks = ti_new FVTLoadTaskMap();	// The actual load task, Key is Page Index, Value is Page Load Info, will be used in VTLoadingThread

		for (const auto& Page : NewPages)
		{
			uint32 PageIndex = Page.first;

			// Find a location in PhysicPageTextures
			uint32 Location = FindAvailbleLocation(UsedLocations);

			// Remove old texture info from PhysicPagesMap
			if (PhysicPageTextures[Location] != uint32(-1))
			{
				TI_ASSERT(PhysicPagesMap.find(PhysicPageTextures[Location]) != PhysicPagesMap.end());
				PhysicPagesMap.erase(PhysicPageTextures[Location]);
			}

			// Get Texture load info, add to load task
			TI_ASSERT(VTLoadTasks->find(PageIndex) == VTLoadTasks->end());
			FVTSystem::FPageLoadInfo PageLoadInfo;
			PageLoadInfo.AtlasLocation = Location;
			VTSystem->GetPageLoadInfoByPageIndex(PageIndex, PageLoadInfo);
			VTTaskOrder->push_back(PageIndex);
			(*VTLoadTasks)[PageIndex] = PageLoadInfo;

			// Remember this location's page
			PhysicPageTextures[Location] = PageIndex;

			// Remember this page's location in array
			PhysicPagesMap[PageIndex] = Location;
		}

		if (VTTaskOrder->size() > 0)
		{
			// Sort, make IO more efficient
			VTTaskOrder->sort(FSortTask(*VTLoadTasks));

			// Send to Loading thread
			VTLoadingThread->AddLoadingTasks(VTTaskOrder, VTLoadTasks);
		}
		else
		{
			ti_delete VTTaskOrder;
			ti_delete VTLoadTasks;
		}
	}

	int32 FVTAnalysisThread::FindAvailbleLocation(const THMap<uint32, uint32>& UsedLocations)
	{
		int32 Loop = 0;
		while (UsedLocations.find(SearchedLocation) != UsedLocations.end())
		{
			SearchedLocation = (SearchedLocation + 1) % FVTSystem::PPCount;
			++Loop;
			TI_ASSERT(Loop < FVTSystem::PPCount);
		}
		int32 Result = SearchedLocation;
		SearchedLocation = (SearchedLocation + 1) % FVTSystem::PPCount;
		return Result;
	}

	void FVTAnalysisThread::OutputDebugTasks(FVTTaskOrderList& VTTaskOrder, FVTLoadTaskMap& VTLoadTasks)
	{
		for (auto& i : VTTaskOrder)
		{
			_LOG(Log, "[%4d, %4d] %s.\n", VTLoadTasks[i].PageStart.X, VTLoadTasks[i].PageStart.Y, VTLoadTasks[i].TextureName.c_str());
		}
	}

	//////////////////////////////////////////////////////////////////////////

	FVTLoadingThread::FVTLoadingThread()
		: TThread("VTLoadingThread")
	{
	}

	FVTLoadingThread::~FVTLoadingThread()
	{
	}

	void FVTLoadingThread::OnThreadStart()
	{
		TThread::OnThreadStart();
		TThread::IndicateVTLoadingThread();
	}

	void FVTLoadingThread::Run()
	{
		if (VTLoadTaskInfos.size() == 0 && VTLoadingTasks.size() == 0)
		{
			TThread::ThreadSleep(5);
		}
		if (VTLoadTaskInfos.size() > 0)
		{
			CollectTasks();
		}
		else if (VTLoadingTasks.size() > 0)
		{
			DoLoadingTasks();
		}
	}

	void FVTLoadingThread::AddLoadingTasks(FVTAnalysisThread::FVTTaskOrderList* VTTaskOrder, FVTAnalysisThread::FVTLoadTaskMap* InVTLoadTasks)
	{
		TaskMutex.lock();
		VTTaskOrders.push_back(VTTaskOrder);
		VTLoadTaskInfos.push_back(InVTLoadTasks);
		TaskMutex.unlock();
	}

	void FVTLoadingThread::CollectTasks()
	{
		TVector<FVTAnalysisThread::FVTTaskOrderList*> VTTaskOrdersCopy;
		TVector<FVTAnalysisThread::FVTLoadTaskMap*> VTLoadTaskInfosCopy;
		{
			TaskMutex.lock();
			VTTaskOrdersCopy = VTTaskOrders;
			VTLoadTaskInfosCopy = VTLoadTaskInfos;
			VTTaskOrders.clear();
			VTLoadTaskInfos.clear();
			TaskMutex.unlock();
		}

		const int32 Size = (int32)VTTaskOrdersCopy.size();
		FVTLoadingTask Task;
		for (int32 i = 0; i < Size; ++i)
		{
			FVTAnalysisThread::FVTTaskOrderList* TaskList = VTTaskOrdersCopy[i];
			FVTAnalysisThread::FVTLoadTaskMap* TaskMap = VTLoadTaskInfosCopy[i];
			for (auto& t : *TaskList)
			{
				FVTSystem::FPageLoadInfo& Info = (*TaskMap)[t];

				if (Task.Name != Info.TextureName)
				{
					if (!Task.Name.empty())
					{
						VTLoadingTasks.push_back(Task);
					}
					Task.Name = Info.TextureName;
				}

				Task.PageIndex.push_back(Info.PageIndex);
				Task.PageStart.push_back(Info.PageStart);
				Task.AtlasLocation.push_back(Info.AtlasLocation);
			}
			VTLoadingTasks.push_back(Task);

			// Has duplicated tasks.
			TI_ASSERT(0);

			ti_delete TaskList;
			ti_delete TaskMap;
		}
		_LOG(Log, "%d VT Task collected.\n", VTLoadingTasks.size());
	}

	void FVTLoadingThread::DoLoadingTasks()
	{
		FVTLoadingTask Task = VTLoadingTasks.front();
		VTLoadingTasks.pop_front();

		const int32 Pages = (int32)Task.PageIndex.size();

		TVTTextureLoader Loader(Task.Name);
		
		for (int32 i = 0 ; i < Pages; ++ i)
		{
			FVTSystem::FPageLoadResult Result;
			// Load texture region
			int32 StartX = Task.PageStart[i].X * FVTSystem::PPSize;
			int32 StartY = Task.PageStart[i].Y * FVTSystem::PPSize;
			TTexturePtr Texture = Loader.LoadTextureWithRegion(0, StartX, StartY, StartX + FVTSystem::PPSize, StartY + FVTSystem::PPSize);

			// Send to render thread to init render resource of this texture
			ENQUEUE_UNIQUE_RENDER_COMMAND_THREEPARAMETER(FVTAddLoadedPages,
				uint32, PageIndex, Task.PageIndex[i],
				uint32, AtlasLocation, Task.AtlasLocation[i],
				TTexturePtr, TextureData, Texture,
				{
					FVTSystem::Get()->AddVTPageData(PageIndex, AtlasLocation, TextureData);
				});
		}
		
	}
}