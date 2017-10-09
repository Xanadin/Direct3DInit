#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <DirectXMath.h>
#include "dxerr.h"
#include <cassert>
#include <fstream>

#if defined(DEBUG) || defined(_DEBUG)
	#ifndef HR
		#define HR(x) {HRESULT hr=(x); if(FAILED(hr)){DXTrace(__FILEW__, (DWORD)__LINE__, hr, L#x, true);}}
	#endif
#else
	#ifndef HR
		#define HR(x) (x)
	#endif
#endif

#define ReleaseCOM(x) {if(x){ x->Release(); x=0;}}
#define SafeDelete(x) {delete x; x=0;}

class MathHelper
{
public:
	template <typename T>
	static T Clamp(const T& x, const T& low, const T& high)
	{
		return x < low ? low : (x > high ? high : x);
	}
};