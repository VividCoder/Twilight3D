#pragma once
#include "pch.h"
#include "MeshTypes2.h"
#include <vector>

using namespace std;

using namespace Vivid::DataTypes;

namespace Vivid {

	namespace Mesh {

		class Mesh3D
		{
		public:
			
			Mesh3D(int vertices, int indices);
			void SetVertex(int index,Vertex3D* v);
			void SetTri(int index,Tri* t);

		private:

			//vector
			vector<Vertex3D* > vertices;
			vector<Tri* > indices;

		};

		
	}

}