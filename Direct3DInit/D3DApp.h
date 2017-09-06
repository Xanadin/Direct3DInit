#pragma once
#define UNICODE
#include <Windows.h>
#include <d3d11.h>
#include "D3DUtil.h"
#include <string>

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp();

	int Run();

	virtual bool Init();
	virtual void OnResize();
	virtual void UpdateScene() = 0;
	virtual void DrawScene() = 0;
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	bool InitMainWindow();
	bool InitDirect3D();

	// WINDOWS
	HINSTANCE mhAppInst;
	HWND mhMainWnd;

	// FSM
	bool mAppPaused;

	// CLIENT STATS
	int mClientWidth;
	int mClientHeight;
	std::wstring mMainWndCaption;

	// DIRECT3D
	ID3D11Device* mD3DDevice;
	ID3D11DeviceContext* mD3DImmediateContext;
	IDXGISwapChain* mSwapChain;

	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mScreenViewport;

	D3D_DRIVER_TYPE mD3DDriverType;
	UINT m4xMsaaQuality;
	bool mEnable4xMsaa;
};