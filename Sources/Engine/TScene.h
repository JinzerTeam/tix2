/*
TiX Engine v2.0 Copyright (C) 2018
By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

namespace tix
{
	enum E_SCENE_LIST_TYPE
	{
		ESLT_STATIC_SOLID,
		ESLT_DYNAMIC_SOLID,

		ESLT_TRANSLUCENT,

		ESLT_LIGHTS,

		ESLT_COUNT,
	};

	enum E_SCENE_FLAG
	{
		SF_LIGHTS_DIRTY = 1 << 0,
	};

	class TNodeSceneRoot
		: public TNode
	{
		DECLARE_NODE_WITH_CONSTRUCTOR(SceneRoot);
	public:
		virtual ~TNodeSceneRoot();
	};

	class TNodeCamera;

	class TScene
	{
	public:
		TScene();
		virtual ~TScene();

		TI_API void TickAllNodes(float Dt, TNode* Root = nullptr);
		TI_API void UpdateAllNodesTransforms(TNode* Root = nullptr);

		void SetSceneFlag(E_SCENE_FLAG flag, bool enable)
		{
			if (enable)
				Flag |= flag;
			else
				Flag &= ~flag;
		}
		bool HasSceneFlag(E_SCENE_FLAG flag)
		{
			return (Flag & flag) != 0;
		}

		TNodeSceneRoot* GetRoot()
		{
			return NodeRoot;
		}

		TI_API void SetActiveCamera(TNodeCamera* camera);
		TI_API TNodeCamera* GetActiveCamera();

		TI_API TNodeStaticMesh* AddStaticMesh(TMeshBufferPtr InMesh, TMaterialInstancePtr InMInstance, bool bCastShadow, bool bReceiveShadow);
		TI_API TNodeLight* AddLight(const vector3df& Position, float Intensity, const SColor& Color);

		void ResetActiveLists();
		void AddToActiveList(E_SCENE_LIST_TYPE List, TNode * ActiveNode);
	protected:
		void BindLights();

	protected:
		TNodeSceneRoot * NodeRoot;
		uint32 Flag;

		TNodeCamera* DefaultCamera;
		TNodeCamera* ActiveCamera;

		TVector<TNode*> ActiveNodeList[ESLT_COUNT];
	};

} // end namespace tix
