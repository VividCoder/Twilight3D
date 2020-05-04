#include "pch.h"
#include "VertexBuffer3D.h"
#include "VividApp.h"

using namespace Vivid::Buffer::Vertex;
using namespace Diligent;


float* ToFloats(vector<Vivid::DataTypes::Vertex3D*> verts) {

	int siz = verts.size();

	float* rv = new float[(long)((long)siz * 15)];

	long fi = 0;

	for (int i = 0; i < verts.size(); i++) {

		auto v = verts.at(i);

		rv[fi++] = v->Pos.x;
		rv[fi++] = v->Pos.y;
		rv[fi++] = v->Pos.z;

		rv[fi++] = v->UV.x;
		rv[fi++] = v->UV.y;
		rv[fi++] = v->UV.z;

		rv[fi++] = v->Normal.x;
		rv[fi++] = v->Normal.y;
		rv[fi++] = v->Normal.z;

		rv[fi++] = v->Tangent.x;
		rv[fi++] = v->Tangent.y;
		rv[fi++] = v->Tangent.z;

		rv[fi++] = v->BiNormal.x;
		rv[fi++] = v->BiNormal.y;
		rv[fi++] = v->BiNormal.z;

	};

	return rv;

}



VertexBuffer3D::VertexBuffer3D(vector<Vivid::DataTypes::Vertex3D*> verts, vector<Uint32> indices)
{


	float* vdat = ToFloats(verts);

	BufferDesc bufDesc;
	bufDesc.Name = "VertexBuffer3D";
	bufDesc.Usage = USAGE_STATIC;
	bufDesc.BindFlags = BIND_VERTEX_BUFFER;
	bufDesc.uiSizeInBytes = verts.size() * (15 * 4);
	BufferData data;
	data.pData = vdat;
	data.DataSize = verts.size() * (15 * 4);

	auto dev = Vivid::App::VividApp::GetDevice();

	dev->CreateBuffer(bufDesc, &data, &VBuf);

	int inum = indices.size();
	int isize = inum * 4;

	BufferDesc IndBuffDesc;
	IndBuffDesc.Name = "VertexBuffer3D Index buffer";
	IndBuffDesc.Usage = USAGE_STATIC;
	IndBuffDesc.BindFlags = BIND_INDEX_BUFFER;
	IndBuffDesc.uiSizeInBytes = isize;
	BufferData IBData;
	IBData.pData = indices.data();
	IBData.DataSize = isize;
	dev->CreateBuffer(IndBuffDesc, &IBData, &IBuf);

}