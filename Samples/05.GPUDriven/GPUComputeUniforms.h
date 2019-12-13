/*
	TiX Engine v2.0 Copyright (C) 2018~2019
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

BEGIN_UNIFORM_BUFFER_STRUCT(FCameraFrustumUniform)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FFloat4, BBoxMin)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FFloat4, BBoxMax)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER_ARRAY(FFloat4, Planes, [6])
END_UNIFORM_BUFFER_STRUCT(FCameraFrustumUniform)

BEGIN_UNIFORM_BUFFER_STRUCT(FCounterReset)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(uint32, Zero)
END_UNIFORM_BUFFER_STRUCT(FCounterReset)

BEGIN_UNIFORM_BUFFER_STRUCT(FCullUniform)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FFloat4, ViewDir)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FMatrix, ViewProjection)
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER(FUInt4, RTSize)	// xy = Screen RT Size, z = Max Mips
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER_ARRAY(FFloat4, Planes, [6])
	DECLARE_UNIFORM_BUFFER_STRUCT_MEMBER_ARRAY(FFloat4, Padding, [4])
END_UNIFORM_BUFFER_STRUCT(FCullUniform)