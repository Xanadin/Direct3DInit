#pragma once
#define UNICODE
#include "D3DUtil.h"
#include <Windows.h>
#include <DirectXMath.h>

#include <d3d11.h>
#include "GameTimer.h"
#include <string>

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp();

	int Run();

	virtual bool Init();
	virtual void OnResize();
	virtual void UpdateScene(float dt) = 0;
	virtual void DrawScene() = 0;
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

	float AspectRatio() const;

protected:
	bool InitMainWindow();
	bool InitDirect3D();

	bool MyInitDirect3D();

	void CalculateFrameStats();

	// WINDOWS
	HINSTANCE mhAppInst;
	HWND mhMainWnd;

	// FSM
	bool mAppPaused;
	bool mMinimized;
	bool mMaximized;
	bool mResizing;

	// CLIENT STATS
	int mClientWidth;
	int mClientHeight;
	std::wstring mMainWndCaption;
	GameTimer mTimer;

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