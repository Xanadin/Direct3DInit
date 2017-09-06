#include "D3DApp.h"

class InitDirect3DApp : public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
	~InitDirect3DApp();

	bool Init();
	void OnResize();
	void UpdateScene();
	void DrawScene();
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	InitDirect3DApp theApp(hInstance);
	if (!theApp.Init()) return 0;
	return theApp.Run();
}

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance) : 
	D3DApp(hInstance)
{

}

InitDirect3DApp::~InitDirect3DApp()
{

}

void InitDirect3DApp::UpdateScene()
{

}

void InitDirect3DApp::DrawScene()
{
	assert(mD3DImmediateContext);
	assert(mSwapChain);
	mD3DImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Blue));
	mD3DImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	HR(mSwapChain->Present(0, 0));
}

bool InitDirect3DApp::Init()
{
	if (!D3DApp::Init()) return false;
	return true;
}

void InitDirect3DApp::OnResize()
{
	D3DApp::OnResize();
}