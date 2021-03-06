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

//#define TileDetermination_RootSig \
//	"CBV(b0) ," \
//    "DescriptorTable(SRV(t0, numDescriptors=1), UAV(u0)),"

#define TileDetermination_RootSig \
    "DescriptorTable(SRV(t0, numDescriptors=1), UAV(u0)),"

//cbuffer RootConstants : register(b0)
//{
//	float4 Info;	// x, y groups
//};

Texture2D<float4> ScreenUV : register(t0);
RWStructuredBuffer<float> OutputUV : register(u0);	// UAV: Processed indirect commands

#define threadBlockSize 32

static const uint vt_mips[7] = { 64, 32, 16, 8, 4, 2, 1 };
static const int vt_mips_offset[7] = { 0, 4096, 5120, 5376, 5440, 5456, 5460 };

[RootSignature(TileDetermination_RootSig)]
[numthreads(threadBlockSize, threadBlockSize, 1)]
void main(uint3 groupId : SV_GroupID, uint3 threadIDInGroup : SV_GroupThreadID, uint3 dispatchThreadId : SV_DispatchThreadID)
{
	float4 result = ScreenUV[dispatchThreadId.xy];
	uint mip_level = uint(result.z);
	uint vt_mip_size = vt_mips[mip_level];
	result.xy = min(float2(0.999f, 0.999f), result.xy);
	uint2 page = uint2(result.xy * vt_mip_size);
	uint output_index = page.y * vt_mip_size + page.x + vt_mips_offset[mip_level];

	OutputUV[output_index] = 1;
}
