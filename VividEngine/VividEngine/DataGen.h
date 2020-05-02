#pragma once
#include "MeshTypes.h"
#include <vector>

using namespace std;

class DataGen
{
public:

	static vector<Vertex2D*> MakeQuad(float x, float y, float w, float h, float z = 0);

};

