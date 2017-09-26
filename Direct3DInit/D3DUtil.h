#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <DirectXMath.h>
#include "dxerr.h"
#include <cassert>

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

namespace Colors
{
	XMGLOBALCONST DirectX::XMVECTORF32 White   = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST DirectX::XMVECTORF32 Black   = { 0.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST DirectX::XMVECTORF32 Red     = { 1.0f, 0.0f, 0.0f, 1.0f };
	XMGLOBALCONST DirectX::XMVECTORF32 Green   = { 0.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST DirectX::XMVECTORF32 Blue    = { 0.0f, 0.0f, 1.0f, 1.0f };
	XMGLOBALCONST DirectX::XMVECTORF32 Yellow  = { 1.0f, 1.0f, 0.0f, 1.0f };
	XMGLOBALCONST DirectX::XMVECTORF32 Cyan    = { 0.0f, 1.0f, 1.0f, 1.0f };
	XMGLOBALCONST DirectX::XMVECTORF32 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };

	XMGLOBALCONST DirectX::XMVECTORF32 Silver  = { 0.75f, 0.75f, 0.75f, 1.0f };
	XMGLOBALCONST DirectX::XMVECTORF32 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
}

class MathHelper
{
public:
	static const float Pi;
};