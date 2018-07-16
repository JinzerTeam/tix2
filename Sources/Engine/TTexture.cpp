/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#include "stdafx.h"
#include "TImage.h"

namespace tix
{
	void TTexture::AddSurface(int32 Width, int32 Height, const uint8* Data, uint32 DataSize, uint32 RowPitch)
	{
		TSurface * Surface = ti_new TSurface;
		uint32 AlignedDataSize = ti_align4(DataSize);
		Surface->Data = ti_new uint8[AlignedDataSize];
		Surface->DataSize = DataSize;
		Surface->Pitch = RowPitch;
		Surface->Width = Width;
		Surface->Height = Height;
		memcpy(Surface->Data, Data, DataSize);

		Surfaces.push_back(Surface);
	}
}
