#pragma once
#include "Common/interface/BasicMath.hpp"
#include "Graphics/GraphicsTools/interface/MapHelper.hpp"
#include "Graphics/GraphicsTools/interface/GraphicsUtilities.h"

using namespace std;
using namespace Diligent;

struct Vertex2D {

	float3 Pos;
	float2 Uv;
	float4 Col;

};

struct Index {

	int VertexID;

};