#include "pch.h"
#include "Draw2D.h"
#include "VertexBuffer2D.h"
#include "DataGen.h"

using namespace Vivid::Draw;

Draw2D::Draw2D() {

	cRed = cGreen = cBlue = cAlpha = 1.0f;

}

void Draw2D::Bind() {


}

void Draw2D::Release() {


}

void Draw2D::SetBlend(BlendMode mode) {

	bMode = mode;

}

void Draw2D::SetColor(float r, float g, float b, float a)
{

	cRed = r;
	cGreen = g;
	cBlue = b;
	cAlpha = a;

}

void Draw2D::Rect(int x, int y, int w, int h) {

	auto quad = Vivid::DataGen::DataGen::MakeQuad(x, y, w, h);

	Uint32 indices[] =
	{
		0,1,2, 1,2,3,
		0,2,1, 1,3,2
	};

	vector<Uint32> ind;

	ind.resize(0);

	for (int i = 0; i < 12; i++) {

		ind.push_back(indices[i]);

	}


	Vivid::Buffer::Vertex::VertexBuffer2D* vb1 = new Vivid::Buffer::Vertex::VertexBuffer2D(quad,ind);



};

