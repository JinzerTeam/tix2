//
//  Common.h
//  VirtualTexture
//
//  Created by Tirax on 2019/8/11.
//  Copyright © 2019 zhaoshuai. All rights reserved.
//

static constant int VTSize = 16 * 1024;
static constant int PPSize = 256;
static constant int PhysicAtlasSize = 32;
static constant float PAInv = 1.0 / PhysicAtlasSize;

#if (VT_ENABLED)
// VT uv output
struct VTBufferData
{
    half4 color [[color(0)]];
    half4 uv [[color(1)]];
};

typedef struct FragmentShaderArguments {
    texture2d<half> IndirectTexture  [[ id(0) ]];
    texture2d<half> PhysicTexture  [[ id(1) ]];
} VTArguments;

inline float mip_map_level(float2 texture_coordinate, float texture_size) // in texel units
{
    float2  dx_vtc = dfdx(texture_coordinate * texture_size);
    float2  dy_vtc = dfdy(texture_coordinate * texture_size);
    float delta_max_sqr = max(dot(dx_vtc, dx_vtc), dot(dy_vtc, dy_vtc));
    return min(6.0, max(0.0, 0.5 * log2(delta_max_sqr)));
}

inline half4 GetVTTextureCoords(float2 texcoord, float4 VTUVTransform)
{
    float4 TexCoord;
    TexCoord.xy = fract(texcoord) * VTUVTransform.zw + VTUVTransform.xy;
    TexCoord.z = mip_map_level(TexCoord.xy, VTSize);
    TexCoord.w = 1.0;
    return half4(TexCoord);
}

inline half4 GetBaseColor(float2 texcoord,
                          float4 VTUVTransform,
                          texture2d<half> IndirectTexture,
                          texture2d<half> PhysicTexture)
{
    float2 VTCoord = fract(texcoord) * VTUVTransform.zw + VTUVTransform.xy;
    float MipLevel = floor(mip_map_level(VTCoord, VTSize));
    
    constexpr sampler PointSampler(mip_filter::none,
                                   mag_filter::linear,
                                   min_filter::linear,
                                   address::clamp_to_edge);
    half4 Indirect = IndirectTexture.sample(PointSampler, VTCoord, MipLevel);
    // coord in virtual texture -
    int VTMipSize = VTSize / (int)(exp2(MipLevel));
    float2 VTPos = VTCoord * VTMipSize / PPSize;
    float2 Coord = fract(VTPos) * 256 / 258 + 1.0 / 258;
    //float2 Coord = frac(VTPos);
    float2 PPCoord = (floor(float2(Indirect.xy) * 256.f) + Coord) * PAInv;
    
    constexpr sampler LinearSampler(mip_filter::linear,
                                    mag_filter::linear,
                                    min_filter::linear,
                                    address::repeat);
    half4 Color = PhysicTexture.sample(LinearSampler, PPCoord);
    return Color;
    //return PPCoord.xyxy;
}
#else    // VT_ENABLED

inline half4 GetBaseColor(texture2d<half> BaseColorTexture, float2 texcoord)
{
    constexpr sampler LinearSampler(mip_filter::linear,
                                    mag_filter::linear,
                                    min_filter::linear,
                                    address::repeat);
    return BaseColorTexture.sample(LinearSampler, texcoord);
}
#endif