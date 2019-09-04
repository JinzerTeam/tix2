//
//  S_Grass.metal
//  VirtualTexture
//
//  Created by Tirax on 2019/8/11.
//  Copyright © 2019 zhaoshuai. All rights reserved.
//

#include <metal_stdlib>
#include <simd/simd.h>
using namespace metal;

#include "Common.h"
#include "VS_Instanced.h"
#include "PS_VT.h"

vertex VSOutput S_TreeMaskVS(VertexInput vsInput [[ stage_in ]],
                             constant EB_View & EB_View [[ buffer(VBIndex_View) ]],
                             constant EB_Primitive & EB_Primitive [[ buffer(VBIndex_Primitive) ]]
                             )
{
    VSOutput vsOutput;
    
    float3 WorldPosition = GetWorldPosition(vsInput);
    vsOutput.position = EB_View.ViewProjection * float4(WorldPosition, 1.0);
    vsOutput.texcoord0 = GetTextureCoords(vsInput, EB_Primitive.VTUVTransform);
    
    vsOutput.normal = vsInput.normal * 2.0h - 1.0h;
    vsOutput.tangent = vsInput.tangent * 2.0h - 1.0h;
    vsOutput.view = half3(EB_View.ViewPos - WorldPosition);
    
    return vsOutput;
}


#if (VT_ENABLED)
fragment VTBufferData
S_TreeMaskPS(VSOutput input [[stage_in]],
             texture2d<half, access::sample> EB_VTIndirectTexture [[ texture(PBIndex_VTIndirectTexture) ]],
             texture2d<half, access::sample> EB_VTPhysicTexture [[texture(PBIndex_VTPhysicTexture)]],
             constant EB_Primitive & EB_Primitive [[ buffer(PBIndex_Primitive) ]])
{
    VTBufferData Data;
    float4 VTUV = GetVTTextureCoords(input.texcoord0.xy, EB_Primitive.VTUVTransform);
    half4 Color = GetBaseColor(VTUV,
                               EB_VTIndirectTexture,
                               EB_VTPhysicTexture);
    
    //if (Color.w < 0.1h)
    //    discard_fragment();
    
    Data.color = Color;
    Data.uv = half4(VTUV);
    
    return Data;
}

#else   // VT_ENABLED
typedef struct FragmentShaderArguments {
    device float4 * Uniform [[ id(0) ]];
    texture2d<half> TexBaseColor  [[ id(1) ]];
    texture2d<half> TexNormal  [[ id(2) ]];
} FragmentShaderArguments;

fragment half4 S_TreeMaskPS(VSOutput input [[stage_in]],
                            constant FragmentShaderArguments & MI_Args [[ buffer(PBIndex_MaterialInstance) ]],
                            constant EB_Primitive & EB_Primitive [[ buffer(PBIndex_Primitive) ]])
{
    half4 Color = GetBaseColor(MI_Args.TexBaseColor, input.texcoord0.xy);
    
    //if (Color.w < 0.1h)
    //    discard_fragment();
    
    return Color;
}
#endif  // VT_ENABLED
