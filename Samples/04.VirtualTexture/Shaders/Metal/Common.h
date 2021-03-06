//
//  Common.h
//  VirtualTexture
//
//  Created by Tirax on 2019/8/11.
//  Copyright © 2019 zhaoshuai. All rights reserved.
//

#define VT_ENABLED 1
#define VT_USE_TILESHADER 1

typedef enum TiXShaderBufferIndex
{
    VBIndex_Vertices = 0,
    VBIndex_Instances = 1,
    VBIndex_View = 2,
    VBIndex_Primitive = 3,
    
    PBIndex_MaterialInstance = 0,
    PBIndex_VirtualTexture = 1,
    PBIndex_View = 2,
    PBIndex_Primitive = 3,
} TiXShaderBufferIndex;

typedef enum TiXShaderTextureIndex
{
    PBIndex_VTIndirectTexture = 0,
    PBIndex_VTPhysicTexture = 1,
} TiXShaderTextureIndex;

#if (VT_ENABLED)
// VT uv output
struct VTBufferData
{
    half4 color [[color(0)]];
    half4 uv [[color(1)]];
};

#endif
