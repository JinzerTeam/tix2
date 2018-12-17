//#include "S_SSSBlur.hlsli"

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
};

Texture2D TexBaseColor : register(t0);
Texture2D TexDepth : register(t1);	// Unused
Texture2D TexSpecular: register(t2);

SamplerState sampler0 : register(s0);

// A pass-through function for the (interpolated) color data.
//[RootSignature(SSSBlur_RootSig)]
float4 main(PixelShaderInput input) : SV_TARGET
{
	float4 BaseColor = TexBaseColor.Sample(sampler0, input.uv);
	float3 Specular = TexSpecular.Sample(sampler0, input.uv).xyz;

	BaseColor.xyz += Specular;
	return BaseColor;
}