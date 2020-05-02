#pragma once
#include "MeshTypes.h"
#include <vector>

using namespace std;

class VMesh2D
{
public:

	VMesh2D();
	void AddVertex(Vertex2D* vertex);
	void AddIndex(int index);

private:

	vector<Vertex2D*> Vertices;
	vector<Index*> Indices;

};

