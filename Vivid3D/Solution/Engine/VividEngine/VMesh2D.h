#pragma once
#include "MeshTypes2.h"
#include <vector>

using namespace std;
using namespace Vivid::DataTypes;

namespace Vivid {
	namespace Mesh {

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

	}

}