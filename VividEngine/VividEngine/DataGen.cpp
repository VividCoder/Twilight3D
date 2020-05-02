#include "pch.h"
#include "DataGen.h"

/*

vector<Vertex2D*> DataGen::MakeQuad(float x, float y, float w,float h,float z) {

	vector<Vertex2D*> ret;

	Vertex2D* vert;

	vert = new Vertex2D();
	vert->Pos = float3(x, y, 0);
	vert->Col = float4(1, 1, 1, 1);
	vert->Uv = float2(0, 0);

	ret.push_back(vert);

	vert = new Vertex2D();
	vert->Pos = float3(x+w, y, 0);
	vert->Col = float4(1, 1, 1, 1);
	vert->Uv = float2(1, 0);

	ret.push_back(vert);

	vert = new Vertex2D();
	vert->Pos = float3(x+w, y+h, 0);
	vert->Col = float4(1, 1, 1, 1);
	vert->Uv = float2(1, 1);

	ret.push_back(vert);

	vert = new Vertex2D();
	vert->Pos = float3(x, y+h, 0);
	vert->Col = float4(1, 1, 1, 1);
	vert->Uv = float2(0, 1);

	ret.push_back(vert);

	return ret;

};
*/