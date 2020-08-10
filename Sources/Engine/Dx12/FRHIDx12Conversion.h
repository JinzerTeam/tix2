/*
	TiX Engine v2.0 Copyright (C) 2018~2021
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

#if COMPILE_WITH_RHI_DX12

namespace tix
{
	inline DXGI_FORMAT GetDxPixelFormat(E_PIXEL_FORMAT InFormat)
	{
		switch (InFormat)
		{
		case EPF_A8:
			return DXGI_FORMAT_R8_UNORM;
		case EPF_RGBA8:
			return DXGI_FORMAT_R8G8B8A8_UNORM;
		case EPF_RGBA8_SRGB:
			return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case EPF_BGRA8:
			return DXGI_FORMAT_B8G8R8A8_UNORM;
		case EPF_BGRA8_SRGB:
			return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case EPF_R16F:
			return DXGI_FORMAT_R16_FLOAT;
		case EPF_RG16F:
			return DXGI_FORMAT_R16G16_FLOAT;
		case EPF_RGBA16F:
			return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case EPF_R32F:
			return DXGI_FORMAT_R32_FLOAT;
		case EPF_RG32F:
			return DXGI_FORMAT_R32G32_FLOAT;
		case EPF_RGB32F:
			return DXGI_FORMAT_R32G32B32_FLOAT;
		case EPF_RGBA32F:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case EPF_DEPTH16:
			return DXGI_FORMAT_D16_UNORM;
		case EPF_DEPTH32:
			return DXGI_FORMAT_D32_FLOAT;
		case EPF_DEPTH24_STENCIL8:
			return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case EPF_DDS_DXT1:
			return DXGI_FORMAT_BC1_UNORM;
		case EPF_DDS_DXT1_SRGB:
			return DXGI_FORMAT_BC1_UNORM_SRGB;
		case EPF_DDS_DXT3:
			return DXGI_FORMAT_BC2_UNORM;
		case EPF_DDS_DXT3_SRGB:
			return DXGI_FORMAT_BC2_UNORM_SRGB;
		case EPF_DDS_DXT5:
			return DXGI_FORMAT_BC3_UNORM;
		case EPF_DDS_DXT5_SRGB:
			return DXGI_FORMAT_BC3_UNORM_SRGB;
		case EPF_DDS_BC5:
			return DXGI_FORMAT_BC5_UNORM;
		}
		TI_ASSERT(0);
		return DXGI_FORMAT_UNKNOWN;
	};

	static const DXGI_FORMAT k_MESHBUFFER_STREAM_FORMAT_MAP[ESSI_TOTAL] =
	{
		DXGI_FORMAT_R32G32B32_FLOAT,	// ESSI_POSITION,
		DXGI_FORMAT_R8G8B8A8_UNORM,		// ESSI_NORMAL,
		DXGI_FORMAT_R8G8B8A8_UNORM,	// ESSI_COLOR,
		DXGI_FORMAT_R16G16_FLOAT,	// ESSI_TEXCOORD0,
		DXGI_FORMAT_R16G16_FLOAT,	// ESSI_TEXCOORD1,
		DXGI_FORMAT_R8G8B8A8_UNORM,	// ESSI_TANGENT,
		DXGI_FORMAT_R8G8B8A8_UINT,	// ESSI_BLENDINDEX,
		DXGI_FORMAT_R8G8B8A8_UNORM,	// ESSI_BLENDWEIGHT
	};

	static const DXGI_FORMAT k_INSTANCEBUFFER_STREAM_FORMAT_MAP[EISI_TOTAL] =
	{
		DXGI_FORMAT_R32G32B32A32_FLOAT,	// EISI_TRANSITION,
#if USE_HALF_FOR_INSTANCE_ROTATION
		DXGI_FORMAT_R16G16B16A16_FLOAT,	// EISI_ROT_SCALE_MAT0,
		DXGI_FORMAT_R16G16B16A16_FLOAT,	// EISI_ROT_SCALE_MAT1,
		DXGI_FORMAT_R16G16B16A16_FLOAT,	// EISI_ROT_SCALE_MAT2,
#else
		DXGI_FORMAT_R32G32B32A32_FLOAT,	// EISI_ROT_SCALE_MAT0,
		DXGI_FORMAT_R32G32B32A32_FLOAT,	// EISI_ROT_SCALE_MAT1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,	// EISI_ROT_SCALE_MAT2,
#endif
	};

	static const D3D12_BLEND k_BLEND_FUNC_MAP[EBF_COUNT] =
	{
		D3D12_BLEND_ZERO,	//EBF_ZERO,
		D3D12_BLEND_ONE,	//EBF_ONE,
		D3D12_BLEND_SRC_COLOR,	//EBF_SRC_COLOR,
		D3D12_BLEND_INV_SRC_COLOR,	//EBF_ONE_MINUS_SRC_COLOR,
		D3D12_BLEND_DEST_COLOR,	//EBF_DEST_COLOR,
		D3D12_BLEND_INV_DEST_COLOR,	//EBF_ONE_MINUS_DEST_COLOR,
		D3D12_BLEND_SRC_ALPHA,	//EBF_SRC_ALPHA,
		D3D12_BLEND_INV_SRC_ALPHA,	//EBF_ONE_MINUS_SRC_ALPHA,
		D3D12_BLEND_DEST_ALPHA,	//EBF_DST_ALPHA,
		D3D12_BLEND_INV_DEST_ALPHA,	//EBF_ONE_MINUS_DST_ALPHA,
		D3D12_BLEND_SRC1_COLOR,	//EBF_CONSTANT_COLOR,
		D3D12_BLEND_INV_SRC1_COLOR,	//EBF_ONE_MINUS_CONSTANT_COLOR,
		D3D12_BLEND_SRC1_ALPHA,	//EBF_CONSTANT_ALPHA,
		D3D12_BLEND_INV_SRC1_ALPHA,	//EBF_ONE_MINUS_CONSTANT_ALPHA,
		D3D12_BLEND_SRC_ALPHA_SAT,	//EBF_SRC_ALPHA_SATURATE
	};

	static const D3D12_BLEND_OP k_BLEND_EQUATION_MAP[EBE_COUNT] =
	{
		D3D12_BLEND_OP_ADD,	//EBE_FUNC_ADD,
		D3D12_BLEND_OP_SUBTRACT,	//EBE_FUNC_SUBTRACT,
		D3D12_BLEND_OP_REV_SUBTRACT,	//EBE_FUNC_REVERSE_SUBTRACT,
		D3D12_BLEND_OP_MIN,	//EBE_MIN,
		D3D12_BLEND_OP_MAX,	//EBE_MAX
	};

	inline void MakeDx12BlendState(const TPipelineDesc& Desc, D3D12_BLEND_DESC& BlendState)
	{
		BlendState.AlphaToCoverageEnable = FALSE;
		BlendState.IndependentBlendEnable = FALSE;

		D3D12_RENDER_TARGET_BLEND_DESC BlendDesc;
		BlendDesc.BlendEnable = Desc.IsEnabled(EPSO_BLEND);
		BlendDesc.LogicOpEnable = FALSE;
		BlendDesc.SrcBlend = k_BLEND_FUNC_MAP[Desc.BlendState.SrcBlend];
		BlendDesc.DestBlend = k_BLEND_FUNC_MAP[Desc.BlendState.DestBlend];
		BlendDesc.BlendOp = k_BLEND_EQUATION_MAP[Desc.BlendState.BlendOp];
		BlendDesc.SrcBlendAlpha = k_BLEND_FUNC_MAP[Desc.BlendState.SrcBlendAlpha];
		BlendDesc.DestBlendAlpha = k_BLEND_FUNC_MAP[Desc.BlendState.DestBlendAlpha];
		BlendDesc.BlendOpAlpha = k_BLEND_EQUATION_MAP[Desc.BlendState.BlendOpAlpha];
		BlendDesc.LogicOp = D3D12_LOGIC_OP_NOOP;
		BlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		for (int32 i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
			BlendState.RenderTarget[i] = BlendDesc;
	}

	static const D3D12_COMPARISON_FUNC k_COMPARISON_FUNC_MAP[ECF_COUNT] =
	{
		D3D12_COMPARISON_FUNC_NEVER,	//ECF_NEVER,
		D3D12_COMPARISON_FUNC_LESS,	//ECF_LESS,
		D3D12_COMPARISON_FUNC_LESS_EQUAL,	//ECF_LESS_EQUAL,
		D3D12_COMPARISON_FUNC_EQUAL,	//ECF_EQUAL,
		D3D12_COMPARISON_FUNC_GREATER,	//ECF_GREATER,
		D3D12_COMPARISON_FUNC_NOT_EQUAL,	//ECF_NOT_EQUAL,
		D3D12_COMPARISON_FUNC_GREATER_EQUAL,	//ECF_GREATER_EQUAL,
		D3D12_COMPARISON_FUNC_ALWAYS,	//ECF_ALWAYS,
	};
	static const D3D12_STENCIL_OP k_STENCIL_OP_MAP[ESO_COUNT] =
	{
		D3D12_STENCIL_OP_KEEP,	//ESO_KEEP,
		D3D12_STENCIL_OP_ZERO,	//ESO_ZERO,
		D3D12_STENCIL_OP_REPLACE,	//ESO_REPLACE,
		D3D12_STENCIL_OP_INCR_SAT,	//ESO_INCR_SAT,
		D3D12_STENCIL_OP_DECR_SAT,	//ESO_DECR_SAT,
		D3D12_STENCIL_OP_INVERT,	//ESO_INVERT,
		D3D12_STENCIL_OP_INCR,	//ESO_INCR,
		D3D12_STENCIL_OP_DECR,	//ESO_DECR,
	};

	inline void MakeDx12DepthStencilState(const TPipelineDesc& Desc, D3D12_DEPTH_STENCIL_DESC& DepthStencilState)
	{
		DepthStencilState.DepthEnable = Desc.IsEnabled(EPSO_DEPTH) || Desc.IsEnabled(EPSO_DEPTH_TEST);
		DepthStencilState.DepthWriteMask = Desc.IsEnabled(EPSO_DEPTH) ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO;
		DepthStencilState.DepthFunc = Desc.IsEnabled(EPSO_DEPTH_TEST) ? k_COMPARISON_FUNC_MAP[Desc.DepthStencilDesc.DepthFunc] : D3D12_COMPARISON_FUNC_ALWAYS;
		DepthStencilState.StencilEnable = Desc.IsEnabled(EPSO_STENCIL);
		DepthStencilState.StencilReadMask = Desc.DepthStencilDesc.StencilReadMask;
		DepthStencilState.StencilWriteMask = Desc.DepthStencilDesc.StencilWriteMask;

		DepthStencilState.FrontFace.StencilFailOp = k_STENCIL_OP_MAP[Desc.DepthStencilDesc.FrontFace.StencilFailOp];
		DepthStencilState.FrontFace.StencilDepthFailOp = k_STENCIL_OP_MAP[Desc.DepthStencilDesc.FrontFace.StencilDepthFailOp];
		DepthStencilState.FrontFace.StencilPassOp = k_STENCIL_OP_MAP[Desc.DepthStencilDesc.FrontFace.StencilPassOp];
		DepthStencilState.FrontFace.StencilFunc = k_COMPARISON_FUNC_MAP[Desc.DepthStencilDesc.FrontFace.StencilFunc];

		DepthStencilState.BackFace.StencilFailOp = k_STENCIL_OP_MAP[Desc.DepthStencilDesc.BackFace.StencilFailOp];
		DepthStencilState.BackFace.StencilDepthFailOp = k_STENCIL_OP_MAP[Desc.DepthStencilDesc.BackFace.StencilDepthFailOp];
		DepthStencilState.BackFace.StencilPassOp = k_STENCIL_OP_MAP[Desc.DepthStencilDesc.BackFace.StencilPassOp];
		DepthStencilState.BackFace.StencilFunc = k_COMPARISON_FUNC_MAP[Desc.DepthStencilDesc.BackFace.StencilFunc];
	}

	static const D3D12_FILL_MODE k_FILL_MODE_MAP[EFM_COUNT] =
	{
		D3D12_FILL_MODE_WIREFRAME,	//EFM_WIREFRAME,
		D3D12_FILL_MODE_SOLID,	//EFM_SOLID,
	};

	static const D3D12_CULL_MODE k_CULL_MODE_MAP[ECM_COUNT] =
	{
		D3D12_CULL_MODE_NONE,	//ECM_NONE,
		D3D12_CULL_MODE_FRONT,	//ECM_FRONT,
		D3D12_CULL_MODE_BACK,	//ECM_BACK
	};
	inline void MakeDx12RasterizerDesc(const TPipelineDesc& Desc, D3D12_RASTERIZER_DESC& RasterizerDesc)
	{
		RasterizerDesc.FillMode = k_FILL_MODE_MAP[Desc.RasterizerDesc.FillMode];
		RasterizerDesc.CullMode = k_CULL_MODE_MAP[Desc.RasterizerDesc.CullMode];
		RasterizerDesc.FrontCounterClockwise = TRUE;
		RasterizerDesc.DepthBias = Desc.RasterizerDesc.DepthBias;
		RasterizerDesc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		RasterizerDesc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		RasterizerDesc.DepthClipEnable = TRUE;
		RasterizerDesc.MultisampleEnable = Desc.RasterizerDesc.MultiSampleCount != 0;
		RasterizerDesc.AntialiasedLineEnable = FALSE;
		RasterizerDesc.ForcedSampleCount = 0;
		RasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	}

	static const D3D12_PRIMITIVE_TOPOLOGY_TYPE k_PRIMITIVE_D3D12_TYPE_MAP[EPT_COUNT] =
	{
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,	//EPT_POINTLIST,
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,	//EPT_LINES,
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED,	//EPT_LINESTRIP,
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,	//EPT_TRIANGLELIST,
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED,	//EPT_TRIANGLESTRIP,
	};

	static const D3D_PRIMITIVE_TOPOLOGY k_PRIMITIVE_TYPE_MAP[EPT_COUNT] =
	{
		D3D_PRIMITIVE_TOPOLOGY_POINTLIST,	//EPT_POINTLIST,
		D3D_PRIMITIVE_TOPOLOGY_LINELIST,	//EPT_LINES,
		D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,	//EPT_LINESTRIP,
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,	//EPT_TRIANGLELIST,
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,	//EPT_TRIANGLESTRIP,
	};

	static const E_RENDER_RESOURCE_HEAP_TYPE Dx2TiXHeapMap[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES] =
	{
		EHT_SHADER_RESOURCE,//D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV = 0,
		EHT_SAMPLER,		//D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER = (D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV + 1) ,
		EHT_RENDERTARGET,	//D3D12_DESCRIPTOR_HEAP_TYPE_RTV = (D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER + 1) ,
		EHT_DEPTHSTENCIL,	//D3D12_DESCRIPTOR_HEAP_TYPE_DSV = (D3D12_DESCRIPTOR_HEAP_TYPE_RTV + 1) ,
	};

	inline E_RENDER_RESOURCE_HEAP_TYPE GetTiXHeapTypeFromDxHeap(D3D12_DESCRIPTOR_HEAP_TYPE DxHeap)
	{
		return Dx2TiXHeapMap[DxHeap];
	}

	static const D3D12_DESCRIPTOR_HEAP_TYPE TiX2DxHeapMap[EHT_COUNT] =
	{
		D3D12_DESCRIPTOR_HEAP_TYPE_RTV,			//EHT_RENDERTARGET = 0,
		D3D12_DESCRIPTOR_HEAP_TYPE_DSV,			//EHT_DEPTHSTENCIL,
		D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,		//EHT_SAMPLER,
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,	//EHT_UNIFORMBUFFER,
	};

	inline D3D12_DESCRIPTOR_HEAP_TYPE GetDxHeapTypeFromTiXHeap(E_RENDER_RESOURCE_HEAP_TYPE TiXHeap)
	{
		return TiX2DxHeapMap[TiXHeap];
	}

	static const D3D12_FILTER TiX2DxTextureFilterMap[ETFT_COUNT] =
	{
		D3D12_FILTER_MIN_MAG_MIP_POINT,	//ETFT_MINMAG_NEAREST_MIP_NEAREST = 0,
		D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT,	//ETFT_MINMAG_LINEAR_MIP_NEAREST,
		D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR,	//ETFT_MINMAG_NEAREST_MIPMAP_LINEAR,
		D3D12_FILTER_MIN_MAG_MIP_LINEAR,	//ETFT_MINMAG_LINEAR_MIPMAP_LINEAR,
	};

	inline D3D12_FILTER GetDxTextureFilterFromTiX(E_TEXTURE_FILTER_TYPE Filter)
	{
		return TiX2DxTextureFilterMap[Filter];
	}

	static const D3D12_TEXTURE_ADDRESS_MODE TiX2DxTextureAddressMode[ETC_COUNT] =
	{
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,	//ETC_REPEAT = 0,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,	//ETC_CLAMP_TO_EDGE,
		D3D12_TEXTURE_ADDRESS_MODE_MIRROR,	//ETC_MIRROR,
	};

	inline D3D12_TEXTURE_ADDRESS_MODE GetDxTextureAddressModeFromTiX(E_TEXTURE_ADDRESS_MODE AddressMode)
	{
		return TiX2DxTextureAddressMode[AddressMode];
	}

	static const D3D12_SHADER_VISIBILITY TiX2DxShaderStage[ESS_COUNT] = 
	{
		D3D12_SHADER_VISIBILITY_VERTEX,	//ESS_VERTEX_SHADER,
		D3D12_SHADER_VISIBILITY_PIXEL,	//ESS_PIXEL_SHADER,
		D3D12_SHADER_VISIBILITY_DOMAIN,	//ESS_DOMAIN_SHADER,
		D3D12_SHADER_VISIBILITY_HULL,	//ESS_HULL_SHADER,
		D3D12_SHADER_VISIBILITY_GEOMETRY,	//ESS_GEOMETRY_SHADER,
	};

	inline D3D12_SHADER_VISIBILITY GetDxShaderVisibilityFromTiX(E_SHADER_STAGE ShaderStage)
	{
		return TiX2DxShaderStage[ShaderStage];
	}


	static const D3D12_RESOURCE_STATES TiX2DxResourceStateMap[RESOURCE_STATE_NUM] =
	{
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
		D3D12_RESOURCE_STATE_INDEX_BUFFER,
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		D3D12_RESOURCE_STATE_DEPTH_READ,
		D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		D3D12_RESOURCE_STATE_STREAM_OUT,
		D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT,
		D3D12_RESOURCE_STATE_COPY_DEST,
		D3D12_RESOURCE_STATE_COPY_SOURCE,
		D3D12_RESOURCE_STATE_COMMON,	// for RESOURCE_STATE_MESHBUFFER, do NOT use this value.
	};

	static const D3D12_RESOURCE_DIMENSION TiX2DxResourceDimension[ETT_TEXTURE_TYPE_NUM] =
	{
		D3D12_RESOURCE_DIMENSION_TEXTURE1D,	//ETT_TEXTURE_1D,
		D3D12_RESOURCE_DIMENSION_TEXTURE2D,	//ETT_TEXTURE_2D,
		D3D12_RESOURCE_DIMENSION_TEXTURE3D,	//ETT_TEXTURE_3D,

		D3D12_RESOURCE_DIMENSION_UNKNOWN,	//ETT_TEXTURE_CUBE,

		D3D12_RESOURCE_DIMENSION_UNKNOWN	//ETT_TEXTURE_UNKNOWN,
	};	
	inline D3D12_RESOURCE_DIMENSION GetTextureTypeFromTiX(E_TEXTURE_TYPE Type)
	{
		return TiX2DxResourceDimension[Type];
	}

}
#endif	// COMPILE_WITH_RHI_DX12