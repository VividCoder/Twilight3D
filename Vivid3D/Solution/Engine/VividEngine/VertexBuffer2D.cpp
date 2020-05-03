#include "pch.h"
#include "VertexBuffer2D.h"
#include "VividApp.h"


using namespace Vivid::Buffer::Vertex;
using namespace Diligent;

float* ToFloats(vector<Vivid::DataTypes::Vertex2D*> verts) {

	int siz = verts.size();

	float* rv = new float[siz*9];

	int fi = 0;

	for (int i = 0; i < verts.size(); i++) {

		auto v = verts.at(i);

		rv[fi++] = v->Pos.x;
		rv[fi++] = v->Pos.y;
		rv[fi++] = v->Pos.z;

		rv[fi++] = v->Col.x;
		rv[fi++] = v->Col.y;
		rv[fi++] = v->Col.z;
		rv[fi++] = v->Col.w;

		rv[fi++] = v->Uv.x;
		rv[fi++] = v->Uv.y;

	};

	return rv;

}

VertexBuffer2D::VertexBuffer2D(vector<Vivid::DataTypes::Vertex2D*> verts,vector<Uint32> indices)
{


	float* vdat = ToFloats(verts);

	BufferDesc bufDesc;
	bufDesc.Name = "VertexBuffer2D";
	bufDesc.Usage = USAGE_STATIC;
	bufDesc.BindFlags = BIND_VERTEX_BUFFER;
	bufDesc.uiSizeInBytes = verts.size() * (9 * 4);
	BufferData data;
	data.pData = vdat;
	data.DataSize = verts.size() * (9 * 4);
	
	auto dev = Vivid::App::VividApp::GetDevice();

	dev->CreateBuffer(bufDesc, &data, &VBuf);

	int inum = indices.size();
	int isize = inum * 4;

	BufferDesc IndBuffDesc;
	IndBuffDesc.Name = "Cube index buffer";
	IndBuffDesc.Usage = USAGE_STATIC;
	IndBuffDesc.BindFlags = BIND_INDEX_BUFFER;
	IndBuffDesc.uiSizeInBytes = isize;
	BufferData IBData;
	IBData.pData = indices.data();
	IBData.DataSize = isize;
	dev->CreateBuffer(IndBuffDesc, &IBData, &IBuf);


}