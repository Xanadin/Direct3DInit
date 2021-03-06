#pragma once
#include "D3DUtil.h"
#include <vector>
class GeometryGenerator
{
public:
	struct Vertex
	{
		Vertex() {};
		Vertex(const DirectX::XMFLOAT3& p, const DirectX::XMFLOAT3& n, const DirectX::XMFLOAT3& t, const DirectX::XMFLOAT2& uv)
			: Position(p), Normal(n), TangentU(t), TexC(uv){}
		Vertex(
				float px, float py, float pz,
				float nx, float ny, float nz,
				float tx, float ty, float tz,
				float u, float v)
		: Position(px, py, pz), Normal(nx, ny, nz), TangentU(tx, ty, tz), TexC(u, v){}

		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT3 TangentU;
		DirectX::XMFLOAT2 TexC;
	};
	struct MeshData
	{
		std::vector<Vertex> Vertices;
		std::vector<UINT> Indices;
	};

	void CreateBox(float width, float height, float depth, MeshData& meshData);
	void CreateSphere();
	void CreateGeoSphere();
	void CreateCylinder();
	void CreateGrid(float width, float depth, UINT m, UINT n, MeshData& meshData);
	void CreateFullScreenQuad(MeshData& meshData);
private:

};