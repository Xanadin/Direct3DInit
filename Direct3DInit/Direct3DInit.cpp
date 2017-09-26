#include "D3DApp.h"
#include "d3dx11effect.h"
#include <DirectXColors.h>
#include <d3dcompiler.h>

struct Vertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};

class InitDirect3DApp : public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
	~InitDirect3DApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();
	
private:
	void BuildGeometryBuffers();
	void BuildFX();
	void BuildVertexLayout();

	ID3D11Buffer* mBoxVB;
	ID3D11Buffer* mBoxIB;

	ID3D11InputLayout* mInputLayout;

	ID3DX11Effect* mFX;
	ID3DX11EffectTechnique* mTech;
	ID3DX11EffectMatrixVariable* mfxWorldViewProj;

	DirectX::XMFLOAT4X4 mWorld;
	DirectX::XMFLOAT4X4 mView;
	DirectX::XMFLOAT4X4	mProj;

	float mTheta;
	float mPhi;
	float mRadius;

	POINT mLastMousePos;
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
	D3DApp(hInstance), 
	mBoxVB(0), 
	mBoxIB(0),
	mInputLayout(0),
	mTheta(1.5f * MathHelper::Pi), 
	mPhi(0.25f * MathHelper::Pi),
	mRadius(5.0f),

	mFX(0),
	mTech(0),
	mfxWorldViewProj(0)

{
	mMainWndCaption = L"Box Demo";

	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

	DirectX::XMMATRIX I = DirectX::XMMatrixIdentity();
	DirectX::XMStoreFloat4x4(&mWorld, I);
	DirectX::XMStoreFloat4x4(&mView, I);
	DirectX::XMStoreFloat4x4(&mProj, I);
}

InitDirect3DApp::~InitDirect3DApp()
{
	ReleaseCOM(mBoxVB);
	ReleaseCOM(mBoxIB);

	ReleaseCOM(mFX);

	ReleaseCOM(mInputLayout);
}

void InitDirect3DApp::UpdateScene(float dt)
{
	// Convert Spherical to Cartesian coordinates.
	float x = mRadius * sinf(mPhi) * cosf(mTheta);
	float z = mRadius * sinf(mPhi) * sinf(mTheta);
	float y = mRadius * cosf(mPhi);

	// Build the view matrix.
	DirectX::XMVECTOR pos = DirectX::XMVectorSet(x, y, z, 1.0f);
	DirectX::XMVECTOR target = DirectX::XMVectorZero();
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	DirectX::XMMATRIX V = DirectX::XMMatrixLookAtLH(pos, target, up);
	DirectX::XMStoreFloat4x4(&mView, V);
}

void InitDirect3DApp::DrawScene()
{
	assert(mD3DImmediateContext);
	assert(mSwapChain);
	mD3DImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Blue));
	mD3DImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	mD3DImmediateContext->IASetInputLayout(mInputLayout);
	mD3DImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	mD3DImmediateContext->IASetVertexBuffers(0, 1, &mBoxVB, &stride, &offset);
	mD3DImmediateContext->IASetIndexBuffer(mBoxIB, DXGI_FORMAT_R32_UINT, 0);

	DirectX::XMMATRIX world = DirectX::XMLoadFloat4x4(&mWorld);
	DirectX::XMMATRIX view =  DirectX::XMLoadFloat4x4(&mView);
	DirectX::XMMATRIX proj =  DirectX::XMLoadFloat4x4(&mProj);
	DirectX::XMMATRIX worldViewProj = world * view * proj;

	HR(mSwapChain->Present(0, 0));
}

bool InitDirect3DApp::Init()
{
	if (!D3DApp::Init()) return false;
	BuildGeometryBuffers();
	BuildFX();
	BuildVertexLayout();
	return true;
}

void InitDirect3DApp::OnResize()
{
	D3DApp::OnResize();
	// The window resized, so update the aspect ratio and recompute the projection matrix.
	DirectX::XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	DirectX::XMStoreFloat4x4(&mProj, P);
}

void InitDirect3DApp::BuildGeometryBuffers()
{
	// Create vertex buffer
	Vertex vertices[] =
	{
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4((const float*)&Colors::White  ) },
		{ DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f), DirectX::XMFLOAT4((const float*)&Colors::Black  ) },
		{ DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f), DirectX::XMFLOAT4((const float*)&Colors::Red    ) },
		{ DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4((const float*)&Colors::Green  ) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f), DirectX::XMFLOAT4((const float*)&Colors::Blue   ) },
		{ DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f), DirectX::XMFLOAT4((const float*)&Colors::Yellow ) },
		{ DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f), DirectX::XMFLOAT4((const float*)&Colors::Cyan   ) },
		{ DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f), DirectX::XMFLOAT4((const float*)&Colors::Magenta) }
	};

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * 8;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;
	HR(mD3DDevice->CreateBuffer(&vbd, &vinitData, &mBoxVB));

	UINT indices[] =
	{
		// front face
		0, 1, 2,
		0, 2, 3,
		// back face
		4, 6, 5,
		4, 7, 6,
		// left face
		4, 5, 1,
		4, 1, 0,
		// right face
		3, 2, 6,
		3, 6, 7,
		// top face
		1, 5, 6,
		1, 6, 2,
		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * 36;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	HR(mD3DDevice->CreateBuffer(&ibd, &iinitData, &mBoxIB));
}

void InitDirect3DApp::BuildFX()
{
	DWORD shaderFlags = 0;
	#if defined(DEBUG) | defined(_DEBUG)
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
	#endif

	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	HRESULT hr;

	HR(D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, mD3DDevice, &mFX));
	ReleaseCOM(compiledShader);
	mTech = mFX->GetTechniqueByName("ColorTech");
	mfxWorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix;
}

void InitDirect3DApp::BuildVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3DX11_PASS_DESC passDesc;

	HR(mD3DDevice->CreateInputLayout(vertexDesc, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &mInputLayout));
}