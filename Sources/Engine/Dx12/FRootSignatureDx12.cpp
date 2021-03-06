/*
	TiX Engine v2.0 Copyright (C) 2018~2021
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"

#if COMPILE_WITH_RHI_DX12
#include "FRootSignatureDx12.h"
#include "FRHIDx12.h"
#include "FRHIDx12Conversion.h"

namespace tix
{
	static const D3D12_SHADER_VISIBILITY Dx12ShaderVisibilityMap[ESS_COUNT] =
	{
		D3D12_SHADER_VISIBILITY_VERTEX,	//ESS_VERTEX_SHADER,
		D3D12_SHADER_VISIBILITY_PIXEL,	//ESS_PIXEL_SHADER,
		D3D12_SHADER_VISIBILITY_DOMAIN,	//ESS_DOMAIN_SHADER,
		D3D12_SHADER_VISIBILITY_HULL,	//ESS_HULL_SHADER,
		D3D12_SHADER_VISIBILITY_GEOMETRY,	//ESS_GEOMETRY_SHADER,
	};

	void FRootSignatureDx12::Finalize(FRHI * RHI)
	{
		FRHIDx12 * RHIDx12 = static_cast<FRHIDx12*>(RHI);

		D3D12_ROOT_SIGNATURE_FLAGS RootSignatureFlags =
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | // Only the input assembler stage needs access to the constant buffer.
			D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
			D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS;

		Finalize(RHIDx12->GetD3dDevice().Get(), RootSignatureFlags);
	}

	void FRootSignatureDx12::InitStaticSampler(
		uint32 Register,
		const D3D12_SAMPLER_DESC& NonStaticSamplerDesc,
		D3D12_SHADER_VISIBILITY Visibility)
	{
		TI_ASSERT(NumInitializedStaticSamplers < SamplerArray.size());
		D3D12_STATIC_SAMPLER_DESC& StaticSamplerDesc = SamplerArray[NumInitializedStaticSamplers];
		++NumInitializedStaticSamplers;

		StaticSamplerDesc.Filter = NonStaticSamplerDesc.Filter;
		StaticSamplerDesc.AddressU = NonStaticSamplerDesc.AddressU;
		StaticSamplerDesc.AddressV = NonStaticSamplerDesc.AddressV;
		StaticSamplerDesc.AddressW = NonStaticSamplerDesc.AddressW;
		StaticSamplerDesc.MipLODBias = NonStaticSamplerDesc.MipLODBias;
		StaticSamplerDesc.MaxAnisotropy = NonStaticSamplerDesc.MaxAnisotropy;
		StaticSamplerDesc.ComparisonFunc = NonStaticSamplerDesc.ComparisonFunc;
		StaticSamplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
		StaticSamplerDesc.MinLOD = NonStaticSamplerDesc.MinLOD;
		StaticSamplerDesc.MaxLOD = NonStaticSamplerDesc.MaxLOD;
		StaticSamplerDesc.ShaderRegister = Register;
		StaticSamplerDesc.RegisterSpace = 0;
		StaticSamplerDesc.ShaderVisibility = Visibility;

		if (StaticSamplerDesc.AddressU == D3D12_TEXTURE_ADDRESS_MODE_BORDER ||
			StaticSamplerDesc.AddressV == D3D12_TEXTURE_ADDRESS_MODE_BORDER ||
			StaticSamplerDesc.AddressW == D3D12_TEXTURE_ADDRESS_MODE_BORDER)
		{
			if (NonStaticSamplerDesc.BorderColor[3] == 1.0f)
			{
				if (NonStaticSamplerDesc.BorderColor[0] == 1.0f)
					StaticSamplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
				else
					StaticSamplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
			}
			else
				StaticSamplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		}
	}

	void FRootSignatureDx12::InitStaticSampler(
		uint32 Register,
		const D3D12_STATIC_SAMPLER_DESC& InStaticSamplerDesc)
	{
		TI_ASSERT(NumInitializedStaticSamplers < SamplerArray.size());
		D3D12_STATIC_SAMPLER_DESC& StaticSamplerDesc = SamplerArray[NumInitializedStaticSamplers];
		++NumInitializedStaticSamplers;

		StaticSamplerDesc = InStaticSamplerDesc;
	}

	void FRootSignatureDx12::Finalize(ID3D12Device* D3dDevice, D3D12_ROOT_SIGNATURE_FLAGS Flags)
	{
		if (Finalized)
			return;

		TI_ASSERT(NumInitializedStaticSamplers == SamplerArray.size());

		D3D12_ROOT_SIGNATURE_DESC RootDesc;
		RootDesc.NumParameters = (uint32)ParamArray.size();
		RootDesc.pParameters = (const D3D12_ROOT_PARAMETER*)(&ParamArray[0]);
		RootDesc.NumStaticSamplers = (uint32)SamplerArray.size();
		RootDesc.pStaticSamplers = SamplerArray.data();
		RootDesc.Flags = Flags;

		ComPtr<ID3DBlob> pOutBlob, pErrorBlob;
		
		VALIDATE_HRESULT(D3D12SerializeRootSignature(&RootDesc, D3D_ROOT_SIGNATURE_VERSION_1,
			pOutBlob.GetAddressOf(), pErrorBlob.GetAddressOf()));

		VALIDATE_HRESULT(D3dDevice->CreateRootSignature(0, pOutBlob->GetBufferPointer(), pOutBlob->GetBufferSize(), IID_PPV_ARGS(&Signature)));

		Signature->SetName(L"RootSignature");
		
		Finalized = true;
	}
}
#endif	// COMPILE_WITH_RHI_DX12