/*
	TiX Engine v2.0 Copyright (C) 2018~2019
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

#include "FUniformBufferView.h"
#include "FSceneDelegate.h"

namespace tix
{
	class FSceneLights;
	class FScene
	{
	public:
		FScene();
		~FScene();

		// Scene flags clear every frames
		enum SceneFlag
		{
			ViewProjectionDirty = 1 << 0,
			ScenePrimitivesDirty = 1 << 1,
			EnvironmentDirty = 1 << 2,

			ViewUniformDirty = (ViewProjectionDirty | EnvironmentDirty),
		};

		void InitRenderFrame();

		void SetViewProjection(const FViewProjectionInfo& Info);
		void SetEnvironmentInfo(const FEnvironmentInfo& Info);

		// Add / Remove primitives from the same static mesh
		void AddStaticMeshPrimitives(const TVector<FPrimitivePtr>& Primitives);
		void RemoveStaticMeshPrimitives(const TVector<FPrimitivePtr>& Primitives);

		void AddSceneTileInfo(TSceneTileResourcePtr SceneTileResource);
		void RemoveSceneTileInfo(TSceneTileResourcePtr SceneTileResource);

		TI_API void RegisterSceneDelegate(FSceneDelegate * InSceneDelegate);

		bool HasSceneFlag(SceneFlag Flag) const
		{
			return (SceneFlags & Flag) != 0;
		}

		void SetSceneFlag(SceneFlag Flag)
		{
			SceneFlags |= Flag;
		}

		void ClearSceneFlags()
		{
			SceneFlags = 0;
		}

		FSceneLights * GetSceneLights()
		{
			return SceneLights;
		}

		const FViewProjectionInfo& GetViewProjection() const
		{
			return ViewProjection;
		}

		const FEnvironmentInfo& GetEnvironmentInfo() const
		{
			return EnvInfo;
		}

		const TVector<FPrimitivePtr>& GetStaticDrawList(E_DRAWLIST_TYPE List) const
		{
			return StaticDrawLists[List];
		}

		FViewUniformBufferPtr GetViewUniformBuffer()
		{
			return ViewUniformBuffer;
		}
	private:
		void PrepareViewUniforms();

	private:
		FSceneDelegate * SceneDelegate;
		FSceneLights * SceneLights;

		// Scene flags per frame, will be cleared by the end of this frame
		uint32 SceneFlags;

		FViewProjectionInfo ViewProjection;
		FEnvironmentInfo EnvInfo;

		// Uniform buffers
		FViewUniformBufferPtr ViewUniformBuffer;

		TVector<FPrimitivePtr> StaticDrawLists[LIST_COUNT];
	};
} // end namespace tix
