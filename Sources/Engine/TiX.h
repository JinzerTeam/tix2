/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/

#pragma once

// Include std symbols
#include <string>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
#include <thread>

using namespace std;

// Disable std container warnings in DLL export
#pragma warning( disable : 4251 )  

// Include tix symbols
#include "TConfig.h"
#include "TDefines.h"
#include "IInstrusivePtr.hpp"
#include "IReferenceCounted.h"
#include "TTypes.h"
#include "TThread.h"
#include "TMath.h"
#include "TInput.h"
#include "TDevice.h"
#include "TLog.h"
#include "TTimer.h"
#include "TFile.h"
#include "TStream.h"

#include "TEngineConfig.h"
#include "TEngine.h"

using namespace tix;