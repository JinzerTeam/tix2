//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#define InstanceFrustumCull_RootSig \
	"CBV(b0) ," \
    "DescriptorTable(SRV(t0, numDescriptors=3), UAV(u0, numDescriptors=1)),"


cbuffer FFrustum : register(b0)
{
	float4 BBoxMin;
	float4 BBoxMax;
	float4 Planes[6];
};

struct FVisibleInfo
{
	uint Visible;
};

struct FBBox
{
	float4 MinEdge;
	float4 MaxEdge;
};

struct FInstanceMetaInfo
{
	// x = primitive index
	uint4 Info;
};

struct FInstanceTransform
{
	float4 ins_transition;
	float4 ins_transform0;
	float4 ins_transform1;
	float4 ins_transform2;
};

StructuredBuffer<FBBox> PrimitiveBBoxes : register(t0);
StructuredBuffer<FInstanceMetaInfo> InstanceMetaInfo : register(t1);
StructuredBuffer<FInstanceTransform> InstanceData : register(t2);

RWStructuredBuffer<FVisibleInfo> VisibleInfo : register(u0);	// Cull result, if this instance is visible

inline bool IntersectPlaneBBox(float4 Plane, float4 MinEdge, float4 MaxEdge)
{
	float3 P;
	P.x = Plane.x >= 0.0 ? MinEdge.x : MaxEdge.x;
	P.y = Plane.y >= 0.0 ? MinEdge.y : MaxEdge.y;
	P.z = Plane.z >= 0.0 ? MinEdge.z : MaxEdge.z;

	float dis = dot(Plane.xyz, P) + Plane.w;
	return dis <= 0.0;
}

inline void TransformBBox(FInstanceTransform Trans, inout float4 MinEdge, inout float4 MaxEdge)
{
	float3 VecMin = MinEdge.xyz;
	float3 VecMax = MaxEdge.xyz;

	float3 Origin = (VecMax + VecMin) * 0.5;
	float3 Extent = (VecMax - VecMin) * 0.5;

	float3 NewOrigin = Origin.xxx * Trans.ins_transform0.xyz;
	NewOrigin = Origin.yyy * Trans.ins_transform1.xyz + NewOrigin;
	NewOrigin = Origin.zzz * Trans.ins_transform2.xyz + NewOrigin;
	NewOrigin += Trans.ins_transition.xyz;

	float3 NewExtent = abs(Extent.xxx * Trans.ins_transform0.xyz);
	NewExtent += abs(Extent.yyy * Trans.ins_transform1.xyz);
	NewExtent += abs(Extent.zzz * Trans.ins_transform2.xyz);

	MinEdge.xyz = NewOrigin - NewExtent;
	MaxEdge.xyz = NewOrigin + NewExtent;
}

#define threadBlockSize 128

[RootSignature(InstanceFrustumCull_RootSig)]
[numthreads(threadBlockSize, 1, 1)]
void main(uint3 groupId : SV_GroupID, uint3 threadIDInGroup : SV_GroupThreadID, uint3 dispatchThreadId : SV_DispatchThreadID)
{
	uint InstanceIndex = dispatchThreadId.x;// groupId.x * threadBlockSize + threadIDInGroup.x;
	uint Result = 0;
	if (InstanceMetaInfo[InstanceIndex].Info.w > 0)
	{
		// This tile intersect view frustum, need to cull instances one by one
		uint PrimitiveIndex = InstanceMetaInfo[InstanceIndex].Info.x;

		// Transform primitive bbox
		float4 MinEdge = PrimitiveBBoxes[PrimitiveIndex].MinEdge;
		float4 MaxEdge = PrimitiveBBoxes[PrimitiveIndex].MaxEdge;
		TransformBBox(InstanceData[InstanceIndex], MinEdge, MaxEdge);

		//if (MinEdge.x <= BBoxMax.x &&
		//	MinEdge.y <= BBoxMax.y &&
		//	MinEdge.z <= BBoxMax.z &&
		//	MaxEdge.x >= BBoxMin.x &&
		//	MaxEdge.y >= BBoxMin.y &&
		//	MaxEdge.z >= BBoxMin.z)
		{
			if (IntersectPlaneBBox(Planes[0], MinEdge, MaxEdge) &&
				IntersectPlaneBBox(Planes[1], MinEdge, MaxEdge) &&
				IntersectPlaneBBox(Planes[2], MinEdge, MaxEdge) &&
				IntersectPlaneBBox(Planes[3], MinEdge, MaxEdge) &&
				IntersectPlaneBBox(Planes[4], MinEdge, MaxEdge) &&
				IntersectPlaneBBox(Planes[5], MinEdge, MaxEdge))
			{
				Result = 1;
			}
		}
	}
	VisibleInfo[InstanceIndex].Visible = Result;
}
